from cs50 import get_string
text = get_string("Text: ")
text = text + " "
letters = 0
words = 0
sentences = 0
for ind, i in enumerate(text):
    if (i >= "A" and i <= "Z") or (i >= "a" and i <= "z"):
        letters += 1
    elif i == " " and ind != 0 and text[ind-1] != " ":
        words += 1
    elif i == "." or i == "!" or i == "?":
        sentences += 1
L = float(letters / words * 100)
S = float(sentences / words * 100)
grade = 0.0588 * L - 0.296 * S - 15.8
if grade >= 16:
    print("Grade 16+")
elif grade < 1:
    print("Before Grade 1")
else:
    print(f"Grade {round(grade)}")
