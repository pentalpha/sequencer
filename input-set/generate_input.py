from random import randint

text = raw_input()

words = text.split(' ',30)

sequence = ""
quantidade_sequencias = 5

cont = 1
while (len(text)) % 5 != 0:
    text = text[:len(text)-1]

tamanho_sequencia = len(text) / quantidade_sequencias

while (len(text) > 0):
    random_position = randint(0,len(text)-1)
    sequence = text[random_position:random_position+tamanho_sequencia]
    text = text.replace(sequence,"")
    print sequence
