import streamlit as st
from string import ascii_lowercase, ascii_uppercase, digits, punctuation

braille_charset = "⠀⠁⠂⠃⠄⠅⠆⠇⠈⠉⠊⠋⠌⠍⠎⠏⠐⠑⠒⠓⠔⠕⠖⠗⠘⠙⠚⠛⠜⠝⠞⠟⠠⠡⠢⠣⠤⠥⠦⠧⠨⠩⠪⠫⠬⠭⠮⠯⠰⠱⠲⠳⠴⠵⠶⠷⠸⠹⠺⠻⠼⠽⠾⠿"

mode_charset_map = {
    'L': ascii_lowercase,
    'U': ascii_uppercase,
    'N': digits,
    'S': punctuation
}

mode_pattern = {
    'L': 2,
    'U': 32,
    'N': 60,
    'S': 16
}

char_patterns = {

    'a': 1,
    'b': 3,
    'c': 9,
    'd': 25,
    'e': 17,
    'f': 11,
    'g': 27,
    'h': 19,
    'i': 10,
    'j': 26,
    'k': 5,
    'l': 7,
    'm': 13,
    'n': 29,
    'o': 21,
    'p': 15,
    'q': 31,
    'r': 23,
    's': 14,
    't': 30,
    'u': 37,
    'v': 39,
    'w': 58,
    'x': 45,
    'y': 61,
    'z': 53,
    'A': 1,
    'B': 3,
    'C': 9,
    'D': 25,
    'E': 17,
    'F': 11,
    'G': 27,
    'H': 19,
    'I': 10,
    'J': 26,
    'K': 5,
    'L': 7,
    'M': 13,
    'N': 29,
    'O': 21,
    'P': 15,
    'Q': 31,
    'R': 23,
    'S': 14,
    'T': 30,
    'U': 37,
    'V': 39,
    'W': 58,
    'X': 45,
    'Y': 61,
    'Z': 53,
    '0': 26,
    '1': 1,
    '2': 3,
    '3': 9,
    '4': 25,
    '5': 17,
    '6': 11,
    '7': 27,
    '8': 19,
    '9': 10,
    '!': 1,
    '@': 3,
    '#': 9,
    '$': 25,
    '%': 17,
    '^': 11,
    '&': 27,
    '*': 19,
    '(': 10,
    ')': 26,
    '-': 5,
    '_': 7,
    '=': 13,
    '+': 29,
    '[': 21,
    ']': 15,
    '{': 31,
    '}': 23,
    ';': 14,
    ':': 30,
    '\'': 37,
    '"': 39,
    ',': 58,
    '.': 45,
    '?': 61,
    '/': 53,
}

def update_mode(char, curr_mode):

    if char in mode_charset_map[curr_mode]:
        return False, curr_mode
    else:
        mode = [key for key, value in mode_charset_map.items() if char in value][0]
        return True, mode

def text2braille(text):

    mode = 'L'

    braille_text = ''
    for char in text:

        if char == ' ':
            braille_text += braille_charset[-1]
            continue

        mode_change, new_mode = update_mode(char, mode)
        if mode_change:
            braille_text += braille_charset[mode_pattern[new_mode]]
            mode = new_mode
        braille_text += braille_charset[char_patterns[char]]
    
    return braille_text


st.title ("Louis Braille Guide")
st.write("This is a simple tool to convert text to braille. It uses the standard 6-dot braille system.")

st.header("Text Input")
text = st.text_area("Enter text to convert to braille")

st.header("Braille Output")
st.markdown(text2braille(text))

st.divider()

st.header(f"Movement Mode (Pattern {braille_charset[48]})")
st.write("In movement mode, use the following keys to move the cursor:")
cols = st.columns(4)

cols[0].write("Up")
cols[0].header(braille_charset[9])

cols[1].write("Down")
cols[1].header(braille_charset[36])

cols[2].write("Left")
cols[2].header(braille_charset[7])

cols[3].write("Right")
cols[3].header(braille_charset[56])
