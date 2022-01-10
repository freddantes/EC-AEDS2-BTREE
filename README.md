# EC-AEDS2-BTREE

## COMPILAÇÃO
Será feita através do MakeFile
```
make clean
make
make run
```
## BASE DE DADOS
A base de dados utilizadas é a do IBGE referente ao censo demográfico de 2010, encontrada no site basedosdados.org
Além disso, a bae de dados, contará com 1.000 entradas conforme orientação do trabalho, sendo que cada página da árvore B contará com 10 dessas entradas, portanto existiriam 100 páginas(arquivos) com 10 entradas cada, totalizando as 1.000 entradas.
## ESTRUTURA
A estrutura utilizada, conforme orientação prévia, será a Árvore B com m = 2, ou seja, cada página guardará de 1 a 3 códigos.
Ademais, a estrutura deverá ser capaz de inserir, remover e pesquisar o cpf, mantendo sempre a estrutura conforme as premissas adotadas.
