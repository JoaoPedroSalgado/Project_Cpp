# Trabalho Poo
 Por João Pedro Salgado e Henrique Marques
 
# Viagens no deserto

Caravanas

Deserto

Mercadorias

Tesouro

Bárbaros

# Mapa:

>> Grelha retangular
>> Mostrar que zonas são deserto, montanhas, cidades e onde estão Caravanas
(seguindo os caracteres no enunciado)

- Zonas de deserto (podem ser percorridas)
- Montanhas (não podem ser percorridas)
- Cidades:
    > Caravanas podem reabastecer, comprar e vender itens

# Caravanas
- Cada caravana tem uma tripulação inicial
- O utilizador pode caçar, ir de cidade a cidade e vender Mercadorias
- Podem apenas estar em posicoes no deserto ou cidade
Se estiver num deserto é visivel 
Se estiver numa cidade deixa de ser visivel diretamente tendo de listar o conteudo da cidade para ver que a caravana existe.
- Identificadas por um numero unico
- Existem diferentes tipos
- Todas transportam mercadoria e tripulantes
- Umas sao mais focadas em transporte de mercadoria, outras para ataque
- O deslocamento de uma caravana corresponde a mover 8 posicoes adjacentes a posicao que esta (lembrar efeito esfera)
- O movimento das caravanas acontece por comando, forma autonoma que varia do tipo de caravana ou por estar sem tripulantes que depende do tipo de caravana
- Por ordem do utilizador:
O utilizador indica a direcao e a caravana desloca-se uma posicao nessa direcao
Dependendo do tipo de caravana essa ordem pode ser dada uma ou mais vezes
- Deslocamento autónomo:
Dependendo do seu tipo
- Descolamento quando nao tem tripulantes:
Depende do seu tipo
- Tem um limite de mercadoria possivel de transportar sendo a unicade de carga "tonelada".
- Tem agua para a tripulacao que vai diminuindo em funcao dos instantes e tripulacao e quando chega a 0 a tripulacao sofre.
- Quando entra numa cidade:
A caravana pode comprar ou vender mercadoria
> O preço de compra e venda é configuravel mas por omissao é compra: 1 por tonelada, venda: 2 por tonelada. Viagens dao sempre lucro
Reabastecer agua para 100% de forma automatica

- Todas as caravanas menos as dos barbaros quando ficam sao agua perdem um tripulante a cada turno.~

- Tipos de caravana:

>> Comércio
- Lenta e fraca mas com grande capacidade de carga
- Desloca 1 ou 2 posições por turno.
- Tem 20 tripulantes
- Leva até 40 toneladas de carga
- Leva até 200 litros de água
- Gasta 2 litros de água por instante
ou 1 litro se tiver menos de 10 tripulantes
ou 0 se nao tiver nenhum
- Deslocacao autonoma:
Tenta se manter ao lado de outra caravana do utilizador para protecao
Se tiver algum item a 2 linhas/colunas desloca-se para o apanhar
- Se for apanhado por uma tempestade:
50% de chance de ser destruido se tiver mais de 20 toneladas de carga utilizadas
25% de chance de ser destruido se tiver menos de 20 toneladas de carga
Se sobreviver perde 25% da carga
- Se ficar sem tripulantes move-se de forma aleatoria e passado 5 instantes a caravana desaparecendo

>> Militar
- Rápida e forte mas não transporta quase nenhuma carga
- Desloca-se até 3 vezes por turno
- Transporta até 40 tripulantes
- Leva até 5 toneledas
- Leva até 400 litros de água
- Gasta 3 litros de água por instante
1 litro se tiver menos de 20 tripulantes incluindo se nao tiver nenhum
- Descolacao autonoma:
Fica parada
Se aparecer alguma caravana bárbara a 6 posicoes de diferenca (linha e coluna) persegue-a.
- Numa tempestade de areia:
Perde 10% dos tripulantes
33% de chance de ser destruída
- Se ficar sem tribulantes move-se na mesma direcao do ultimo movimento que fez quando trinha tripulantes, passado 7 instantes acaba por desaparecer.

>> Secreta
- Caracterisiticas escolhidas por nos

>> Caravanas bárbaras (não disponivel ao utilizador)
- Sempre em modo autonomo:
Anda aleatoriamente uma posicao, 1 por turno a nao ser que
Se vir uma caravana do utilizador a 8 posicoes em linha ou em coluna 
Vai tentar apanhá-la a 1 posição por turno também
- Inicialmente tem 40 bárbaros 
Não precisam de água
por isso podem andar o tempo que quiserem no deserto
- Também apanham items, os efeitos sao iguais
Na arca do tesouro o utilizador ganha moedas
- Numa tempestade de areia:
Perde sempre 10% dos tripulantes
25% de ser destruida
- Se ficar sem tripulantes desaparece imediatamente
- Desaparece passado 60 turnos (configuravel)
- Aparecem em posicao aleatoria de 40 em 40 turnos (configuravel)


# Simulação
- Por turnos
- Cada jogador escreve o comando numa vez só
- Noção de passagem de tempo 
> Unidade instante 
- A cada instante o simulador aplica ações e apresenta no ecrã o resultado
- O utilizador tem x moedas iniciais (que pode ser configuravel) com que pode comprar as suas caravanas iniciais
- As receitas obtidas de vendas pode usar para comprar mais caravanas e tripulação
- O simulador tem caravanas bárbaras que não são do utilizador
Se uma caravana do utilizador se encontrar numa celula do mapa adjacente a uma destas vai haver combate
Os combates podem durar varios instantes
Terminam quando uma caravana é destruida
Adjacencia é apenas (cima, baixo, esquerda, direita e diagonais nao conta)
- A simulação termina quando o utilizador fica sem caravanas e sem dinheiro para comprar novas ou quando escrever "terminar"
No final da simulação deverá ser indicado:
O nº de instantes decorrido
O total de combates que venceu
O nº de moedas que ainda tinha
- O mapa inicial e alguns parametros sao lidos de um ficheiro.
Não é necessario gerar mapa aleatoriamente

# Inicio Simulação
- Duas fases
Primeira, muito curta e simples:
- Especificar o nome do ficheiro de config e ler
Esse ficheiro define o tamanho do mapa do deserto, o mapa e parametros gerais (moedas iniciais, numero de cidades, preços, etc, com todos os valores dito configuravies)
Após o ficheiro lido passa a fase seguinte:

# Desenrolar da simulação
- Segunda fase da simulação, cada turno ocorre os momentos seguintes:
1. Apresentação: Consola informação e mapa da situacao atual
2. Leitura e execução de comandos: O utilizador escreve os comandos que quiser e termina esta etapa com o comando prox
3. Execucao de comportamentos automaticos: Caravanas efetuam os movimentos autonomos (se estiverem nesse modo), podendo apanhar items, etc
4. Bárbaros: Nesta fase podem surgir as caravanas bárbaras. As que já existirem movimentam-se
5. Combates: Apenas considerado depois de todos os comportamentos automaticos
Todos os acontecimentos que produzirem (itens apanhados, combates realizados, etc) devem ser registado e mostrar com o mapa no turno seguinte


# Deserto
- O deserto corresponde a area total onde a simulacao decorre.
- Gerar uma grealha retangular de posicoes
Cada posição pode corresponder a uma montanha, cidade ou estar vazia (é o deserto).
As montanhens, em principio, ocorrem em gurpos de varias posicoes contiguas.
As cidades, estão isoladas e nunca totalmente rodeadas de montanhas (seriam inacessiveis).
- O deserto é esférico. 
Se estiver no topo e subir vou para a posicao mais abaixo
Se estiver no fundo e descer vou para a posicao mais acima.
Se estiver no extremo esquerdo e continuar a ir para esquerda vou parar ao ponto mais extremo a direita
Se estiver no extremo direito e continuar a ir para a direita vou parar ao ponto mais extremo a esquerda
Este conceito apenas afeta os movimentos e nao a visualizacao (se nao conseguiremos implementar é ok)
- Só pode estar uma caravana de cada vez em cada posição de deserto
- Pode haver itens no deserto
- Pode haver tempestades de aleatoriamente provocadas pelo utilizador especificando:
A regiao quadrada afetada indicando o centro (linha e coluna)
O raio - dimensao (quantas posicoes ao redor do centro)
> Dura 1 instante afetanto o que existir dentro da regiao especificada

# Cidade
- Pode ter varias caravanas 
- Ocupa apenas uma posição e deve ter pelo meno um lado acessivel (deserto).
- Permite a entrada de caravanas
- Neutras, não havendo combates entre caravanas e cidades
- Disponiveis para fornecer novos tripolantes, comprar e vender Mercadorias
- Quando uma caravana entra deixa de ser visivel tendo de ser necessario verificar os detalhes da cidade
- Nome unico e apenas uma letra
- O nº de cidades não é fixo sendo o nº que estiver no ficheiro com o mapa inicial.

# Items
- De forma configuravel vão aparecendo items apenas no deserto em posicoes vazias
- Os items permanencem 20 instantes de forma configuravel desaparecendo de seguida.
- Podem ser apanhados por uma caravana de forma adjacente (cima, baixo, esquerda ou direita)
- O item é apanhado automaticamente não sendo uma opcao do utilizador
- Os items tem representacao visual
- Só podem existir 5 (configuravel)
- Novos items spawnam em cada 10 instantes (configuravel)
- O seu tipo é sortedao em igual probabilidade
Os items são mágicos existindo os seguintes tipos:

>> Caixa de Pandora
Tem doenças matando 20% da tripulação da caravana que apanha 

>> Arca do Tesouro
Tem ouro e aumenta 10% as moedas do utilizador

>> Jaula
Adiciona tripulação a caravana sem exceder o seu maximo

>> Mina
Explode e destrói a caravana

>> Surpresa
Inventar qualquer cena xDs

# Compras e vendas
- Quando uma caravana esta na cidade o utilizador pode:
Comprar tripulantes para essa caravana 1 moeda por cada
Vender mercadoria (configuravel) 2 moedas por tunelada esvaziando-a
Comprar mercadoria (configuravel) 1 moeda por tonelada nao podendo exceder a capacidade

- Inicialmente existem caravanas estacionadas em cidades a espera de serem compradas
Quando todas as caravanas sao compradas nao repoe novas
- 1 caravana de cada tipo por cada cidade
- Quando uma caravana é comprada o utilizador ganha controlo dela ficando dentro da cidade até receber ordens de movimento
- Tambem surge na cidade onde foi comprada com tripulacao cheia e deposito cheio de agua
- Podem ser compradas a qualquer instante desde que tenha moedas e haja caravanas Disponiveis
- Cada custa 100 moedas (configuravel)
- Comando especificar a cidade e o tipo

# Combates
- Ocorre sempre que utilizador vs bárbaro estejam adjacentes
- Nº random de 0 ao nº de tripulantes da caravana
- A caravana com o maior numero ganha
- A caravana que ganha perde 20% da tripulacao
- A caravana que perde fica sem o dobro desse valor (desses 20%)
- As caravanas podem fugir no instante/turno seguinte
- Se ficar parada, no turno seguinte volta a have combate
Só acaba quando uma foge ou quando uma (ou ambas) perdem
- Se a caravana ficar sem tripulantes é eliminada de imediato
- Se a caravana foi destruida em combate, a sua agua passa para a caravana vencedora (sem exceder a capacidade maxima)
- Havendo perda de tripulantes, o resultado arredonda para baixo
- Se houver caravanas inimigas em simultaneo a caravana luta com ambas em cada turno 

# Comandos

Caravanas sao identificadas por numeros e cidades por letra (nao repetido)

Comandos fase 1:
- config <nomeFicheiro> 
> Le ficheiro

- sair 
> sair do programa

Comandos fase 2:
- exec <nomeFicheiro> 
> Le linha por linha e executa.
> Cada linha tem a mesma estrutura e texto dos comandos escritos

- prox <n> 
> Termina a escrita de comandos e execcuta os comandos pendentes e comportamentos automaticos
> n é opctional e maior que 0
> Se avancar mais de um instante deve ser apresentado o mapa e informacoes de cada instante

- comprac <C> <T>
> Compra, na cidade C uma caravana dos tipos:
> C = Comércio
> M = Militar
> S = Secreta

- precos 
> Mostra os preços das mercadorias

- cidade <C>
> Mostra conteudo da cidade C (caravanas existentes)

- caravana <C>
> Mostra descricao da caravana C (todos os detalhes)

- compra <N> <M>
> Compra M toneladas de mercadoria para a caravana N
> Tem que estar numa cidade nessa altura

- vende <N>
> Vende toda a mercadoria 
> Tem que estar numa cidade

- move <N> <X>
> Move a caravana com o nº N para a poxicao X:
> D = direita
> E = esquerda
> C = cima
> b = baixo
Diagonais:
> CE = cima-esquerda
> BE - baixo-esquerda
> BD - baixo-dereita

- auto <N>
> Coloca caravana N em auto gestão, passa ao comportamento autonomatico

- stop <N>
- Para o comportamento automatico da caravana N

- barbaro <I> <c>
> Cria caravana bárbara nas coords (l, c)

- areia <l> <c> <r>
> Cria uma tempestade de areia na posicao l
> c = raio
> r = posicoes
(é um quadrado de posicoes)

- moedas <N>
> Add N moedas (pode ser negativo)

- tripul <N> <T>
> Compra T tripulantes para a caravana N 
> Tem que estar numa cidade

- saves <nome>
> Faz uma copia do buffer (apenas aspeto visual, não dados do simulador)
> Armazenada em memoria associando-o ao nome indicado

- loads <nome>
> Da load ao save anteriormente mencionado.
> Permite ver um determinado instante anterior 
> Esta operacao nao altera o estado da simulacao

- lists 
> Lista os nomes das cópias do buffer existentes

- dels <nome>
> Apaga a cópia do buffer em memória

- terminar
> Termina a simulacao
> Simulador regressa a fase 1 onde pode iniciar uma nova simulacao ou sair do programa


# Configuração
Formato:
1. Primeiras duas linhas indicam a dimensao do deserto
2. Conjunto de linhas com o mesmo tamanho
> Com quantos caracteres quantas as colunas do deserto e tantas linhas como o deserto
> '.' = Posição vazia
> '+' = Montanha
> 'letras minúsculas' = cidade
> 'numeros de 0 a 9' = caravanas
> '!' = caravana bárbara

Exemplo que tem os valores configuraveis que devem ser respeitados:

linhas 10 
colunas 20 
...............+++++ 
..........++++++++++ 
..........a+++++++++ 
...1.........+++++++ 
........2.....++++++ 
....+c...........b++ 
...++++..........+++ 
....++............++ 
.....3........!..... 
..........4......... 
moedas 1000 
instantes_entre_novos_itens 10 
duração_item 20 
max_itens 5 
preço_venda_mercadoria 2 
preço_compra_mercadoria 1 
preço_caravana 100 
instantes_entre_novos_barbaros 40 
duração_barbaros 60 



# Buffer

- Informações primeiro escritas no buffer e só depois transcritas para o escritas
- Ter igual ou menor dimensao a consola
- Cada vez que o conteudo é transcrito faz auto scroll up
- Este buffer será encapsulado numa classe com a funcionalidade necessária para pôr caracteres e strings em posições arbitrárias
- Server para armazenar caracteres para serem impressos depois na consola
- Não é relevante leitura de dados via teclado
- Serve de apoio para output

Requisitos:
- Nº de Linhas e Nº de Colunas definido em run time
- Usar o espaço de armazenamento necessário para os carateres difinidos no ponto anterior
- Esvaziar o buffer (ficar só com espaços)
- Passar o conteudo do buffer para a consola. Imprimir na consola o conteudo do buffer usando mecanismos da atual
- Conceito de cursor com coordenadas linha, coluna onde sera impresso o prox caracter
- Mover cursor para uma determinada coluna e linha
- Imprimir os caracteres na pos atual do cursor:
caracter
string
inteiro
Desloca o cursor para o ultimo impresso
- Operacoes de cima a usar o operador << Do lado esquerdo o objeto do buffer e do lado direito os dados ou objetos necessario a funcionalidade
- Será valorizado no futuro usar o operador << para transcrever os dados que os objetos de uma classe representa diretamente para o buffer
na forma: (objeto-buffer << objeto-de-etc)
- Podemos adicionar funcionalidades extra por exemplo desenhar molduras

Possivel implementação:

Responsável por simular um "ecrã virtual" para exibição.
Atributos:
    int linhas, colunas;
    char* matriz; (representação unidimensional da matriz para economizar espaço).
    int cursorLinha, cursorColuna; (posição atual do cursor).
Métodos:
    void clear(); (esvaziar o buffer preenchendo com espaços).
    void moveCursor(int linha, int coluna);
    void write(char c); (escreve caractere na posição atual e avança o cursor).
    void write(const std::string& str); (escreve string e avança).
    Sobrecarga de operator<< para interagir com dados diretamente.


# Restrições

- Nenhum warning, sem instantes_entre_novos_barbaros
- Não podemos usar vetor de vetor
- Entrega 22 de Dezembro

- Relatório completo, ficheiros auxiliares
- Pronto para compilar
