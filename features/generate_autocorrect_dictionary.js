import nspell from 'nspell'
import dictionary from 'dictionary-en'
import { on } from 'events'
import { writeFile, unlink } from 'node:fs/promises'
import { execSync } from 'node:child_process'

const typos = new Map()
const spell = nspell(dictionary)

// Off-by-one column mapping.
const commonMispresses = {
    q: 'w',
    w: 'qr',
    e: 'wr',
    r: 'et',
    t: 'r',
    z: 'u',
    u: 'zi',
    i: 'uo',
    o: 'i',
    a: 's',
    s: 'ad',
    d: 'sf',
    f: 'dg',
    g: 'f',
    h: 'j',
    j: 'hk',
    k: 'jl',
    l: 'kp',
    p: 'l',
    y: 'x',
    x: 'yc',
    c: 'xv',
    v: 'cb',
    b: 'vn',
    n: 'bm',
    m: 'n',
}

function replaceAt(target, offset, char) {
    return target.slice(0, offset) + char + target.slice(offset + char.length)
}

// Generates typos by introducing off-by-one columns, having used staggered keyboards for decades, I still mispress things.
function commonMispressTypos(word) {
    const typos = []

    for (let i = 0; i < word.length; i++) {
        for (const char of commonMispresses[word[i]] ?? '') {
            typos.push(replaceAt(word, i, char))
        }
    }

    return typos
}

// Generates typos by dropping characters.
function missedCharTypos(word) {
    const typos = []

    typos.push(word.slice(1))

    for (let i = 1; i < word.length - 1; i++)
        typos.push(word.slice(0, i) + word.slice(i + 1))

    typos.push(word.slice(0, word.length - 1))

    return typos
}

// Generates typos by swapping neighboring characters.
function transposedCharTypos(word) {
    const typos = []

    for (let i = 1; i < word.length - 1; i++) {
        const a = word[i]
        const b = word[i + 1]
        typos.push(replaceAt(replaceAt(word, i, b), i + 1, a))
    }

    return typos
}

function ngrams(word) {
    const chars = {}
    let prevChar
    for (const char of word) {
        if (prevChar === char) {
            chars[char] ??= 1
            chars[char] += 1
        }
        prevChar = char
    }
    return chars
}

// Some generated typos look like "wheee" (for the word "where"), these are pretty hard to pull off so I am considering these as unnecessary.
function hasUnnecessaryNgrams(typo, word) {
    const a = ngrams(typo)
    const b = ngrams(word)
    for (const char in a) {
        if (a[char] !== b[char]) {
            return true
        }
    }
    return false
}

// Some generated typos can end up overlapping with other, longer typos. These need to be removed (choosing the shorter variants).
function hasOverlaps(typoA, typos) {
    return typos.some(typoB => typoA !== typoB && typoA.startsWith(typoB))
}

function applyBoundary(typo, boundary) {
    switch (boundary) {
        case 'start':
            return `:${typo}`
        case 'end':
            return `${typo}:`
        case 'both':
            return `:${typo}:`
        default:
            return typo
    }
}

function add(word, boundary = 'start') {
        commonMispressTypos(word)
        .concat(missedCharTypos(word))
        .concat(transposedCharTypos(word))

        // Compiler complains about words that are too short.
        .filter(typo => typo.length > 4)
        // Typos can not be substrings of their corrected version.
        .filter(typo => !word.startsWith(typo))
        // Remove hard to pull off typos such as "wheee".
        .filter(typo => !hasUnnecessaryNgrams(typo, word))
        // Remove typos if they appear in a dictionary.
        .filter(typo => !spell.correct(typo))

        .forEach(typo => typos.set(typo, { word, boundary }))
}

function print() {
    return Array
        .from(typos.keys())

        .filter((typo, _idx, typos) => !hasOverlaps(typo, typos))

        .map(typo => [typo, typos.get(typo)])
        .map(([typo, correction]) => [applyBoundary(typo, correction.boundary), correction])
        .map(([typo, correction]) => `${typo} -> ${correction.word}`)

        .join('\n')
}

add('array')
add('assert')
add('assign')
add('async')
add('await')
add('boolean')
add('break')
add('catch')
add('class')
add('concat')
add('console')
add('constructor')
add('continue')
add('debugger')
add('default')
add('delete')
add('document')
add('exclude')
add('export')
add('extend')
add('extract')
add('filter')
add('finally')
add('foreach')
add('function')
add('implement')
add('import')
add('include')
add('infer')
add('instance')
add('interface')
add('interval')
add('keyof')
add('merge')
add('never')
add('number')
add('object')
add('parameter')
add('partial')
add('private')
add('promise')
add('proxy')
add('public')
add('query')
add('readonly')
add('record')
add('reflect')
add('required')
add('return')
add('select')
add('static')
add('string')
add('super')
add('switch')
add('symbol')
add('throw')
add('timeout')
add('undefined')
add('unknown')
add('update')
add('where')
add('while')
add('width')
add('yield')

await writeFile('./features/autocorrect_dictionary.txt', print())
execSync('qmk generate-autocorrect-data ./features/autocorrect_dictionary.txt -kb zsa/voyager -km michaelostermann')
await unlink('./features/autocorrect_dictionary.txt')
