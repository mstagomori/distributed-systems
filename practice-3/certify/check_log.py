log = open("log.txt", "r")

# REQUEST = 1
# GRANT = 2
# RELEASE = 3

prev_line = '0'
counter = 0
erros = 0

for line in log:

    # if previous message was GRANT, this message = RELEASE
    if prev_line[0] == '2' and line[0] != '3':
        print("ERRO: Mensagem RELEASE deve vir após GRANT")
        print("Linha:", counter, line)
        erros += 1
        break

    prev_line = line
    counter += 1

log.close()

if erros == 0:
    print("O arquivo log.txt está correto!")