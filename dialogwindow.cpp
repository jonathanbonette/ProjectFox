#include "dialogwindow.h"
#include "battlewindow.h"
#include "gamedata.h"
#include "battlewindow.h"
#include "dialoghelper.h"
#include <QMovie>

DialogWindow::DialogWindow(QWidget *parent)
    : QMainWindow(parent), currentNode(nullptr)
{
    createWidgets();
}

DialogWindow::~DialogWindow() { delete currentNode; }

// Implementações dos métodos da classe DialogWindow

void DialogWindow::createWidgets()
{
    label = new QLabel(this);

    // Exibe a janela de diálogo
    setFixedSize(640, 480);
    DialogHelper::updateBackground(this, ":/images/assets/backgrounds/1.png");

    // Configurações visuais para o rótulo
    label->setAlignment(Qt::AlignCenter);
    label->setFont(QFont("SansSerif", 10, QFont::Bold));

    leftButton = new QPushButton("Esquerda", this);
    rightButton = new QPushButton("Direita", this);

    // Conecta os botões ao slot handleChoice
    connect(leftButton, &QPushButton::clicked, this, &DialogWindow::handleChoice);
    connect(rightButton, &QPushButton::clicked, this, &DialogWindow::handleChoice);

    // Adiciona o botão "Aceitar o presente"
    acceptGiftButton = new QPushButton("Aceitar o presente", this);
    connect(acceptGiftButton, &QPushButton::clicked, this, &DialogWindow::handleAcceptGift);
    QHBoxLayout *acceptGiftButtonLayout = new QHBoxLayout;
    // Adicione o botão à layout
    acceptGiftButtonLayout->addWidget(acceptGiftButton);
    acceptGiftButton->hide();

    // Adiciona o botão "Pegar os espólios"
    getItemsButton = new QPushButton("Pegar os espólios", this);
    connect(getItemsButton, &QPushButton::clicked, this, &DialogWindow::handleGetItems);
    QHBoxLayout *getItemsButtonLayout = new QHBoxLayout;
    // Adicione o botão à layout
    getItemsButtonLayout->addWidget(getItemsButton);
    getItemsButton->hide();

    // Layout horizontal para os botões (lado a lado)
    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(leftButton);
    buttonLayout->addWidget(rightButton);
    buttonLayout->addWidget(acceptGiftButton);
    buttonLayout->addWidget(getItemsButton);

    // Inicializa a QLabel do inimigo
    npcImgLabel = new QLabel(this);
    npcImgLabel->setAlignment(Qt::AlignCenter);

    QHBoxLayout *centerLayout = new QHBoxLayout;
    centerLayout->addWidget(npcImgLabel);

    // Layout vertical para organizar o rótulo e os botões
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(label);
    layout->addWidget(npcImgLabel);
    layout->addSpacing(40);
    layout->addLayout(buttonLayout);

    // Widget central
    QWidget *centralWidget = new QWidget;
    centralWidget->setLayout(layout);
    setCentralWidget(centralWidget);

    // Criação da árvore de diálogo
    currentNode = new DialogNode("Em uma distante e enigmática terra, você inicia uma jornada repleta de escolhas.\nDiante de vários caminhos bifurcados sua aventura começa.\nCada decisão moldará seu destino, revelando segredos, enfrentando desafios\ne forjando uma história única.\nQual rumo você escolherá nesta trama repleta de mistérios e magia?\n\nPara começar, qual é sua primeira escolha dessa jornada?\n\nVocê decide:","Checar a clareira","Investigar os sons do cânion");
    DialogNode* nodeLeft = new DialogNode("(1)", "Interagir com as criaturas místicas", "Investigar a fonte mágica");
    DialogNode* nodeRight = new DialogNode("(2)", "Seguir o murmúrio", "Ir ao acampamento dos aventureiros");
    DialogNode* nodeLeftLeft = new DialogNode("(3)","Seguir caminho");
    DialogNode* nodeLeftRight = new DialogNode("(4)","Andar em direção do campo aberto","Prosseguir rumo ao desconhecido");
    DialogNode* nodeRightLeft = new DialogNode("(5)","Dar as boas novas ao aventureiro", "Passar pelo portão");
    DialogNode* nodeRightRight = new DialogNode("(6)", "Se preparar para lutar com eles");
    DialogNode* nodeLeftLeftLeft = new DialogNode("(7)");
    DialogNode* nodeLeftRightLeft = new DialogNode("(9)");
    DialogNode* nodeLeftRightRight = new DialogNode("(10)");
    DialogNode* nodeRightLeftLeft = new DialogNode("(11)", "Voltar ao vilarejo");
    DialogNode* nodeRightLeftRight = new DialogNode("(12)", "", "Pegar os espólios e encerrar a jornada");
    DialogNode* nodeRightRightLeft = new DialogNode("(13)","" , "Comemorar com o grupo de aventureiros");
    DialogNode* nodeRightRightRight = new DialogNode("(14)");
    DialogNode* nodeRightRightLeftRight = new DialogNode("(16)", "", "Encerrar o dia");
    DialogNode* nodeRightLeftLeftLeft = new DialogNode("(17)");
    DialogNode* nodeRightLeftRightRight = new DialogNode("(19)");
    DialogNode* nodeRightLeftRightRightRight = new DialogNode("(20)");


    currentNode->setLeftChild(nodeLeft);
    currentNode->setRightChild(nodeRight);

    // Configura as relações entre os nós
    nodeLeft->setLeftChild(nodeLeftLeft);
    nodeLeft->setRightChild(nodeLeftRight);
    nodeRight->setLeftChild(nodeRightLeft);
    nodeRight->setRightChild(nodeRightRight);
    nodeLeftLeft->setLeftChild(nodeLeftLeftLeft);
    nodeLeftRight->setLeftChild(nodeLeftRightLeft);
    nodeLeftRight->setRightChild(nodeLeftRightRight);
    nodeRightLeft->setLeftChild(nodeRightLeftLeft);
    nodeRightLeft->setRightChild(nodeRightLeftRight);
    nodeRightRight->setLeftChild(nodeRightRightLeft);
    nodeRightRight->setRightChild(nodeRightRightRight);
    nodeRightRightLeft->setRightChild(nodeRightRightLeftRight);
    nodeRightLeftLeft->setLeftChild(nodeRightLeftLeftLeft);
    nodeRightLeftRight->setRightChild(nodeRightLeftRightRight);
    nodeRightRightLeftRight->setRightChild(nodeRightLeftRightRightRight);

    // Atualiza os textos dos botões com base no nó atual
    leftButton->setText(currentNode->getLeftButtonText());
    rightButton->setText(currentNode->getRightButtonText());

    // Define o texto inicial no rótulo
    label->setText(currentNode->getText());
}

// Função para verificar e criar os nós
void DialogWindow::handleChoice()
{
    if (currentNode) {
        // Verifica qual botão foi clicado
        QPushButton *button = qobject_cast<QPushButton*>(sender());

        // Atualiza o nó atual com base na escolha do usuário
        if (button == leftButton && currentNode->getLeftChild()) {
            currentNode = currentNode->getLeftChild();
        } else if (button == rightButton && currentNode->getRightChild()) {
            currentNode = currentNode->getRightChild();
        }

        // Atualiza o texto exibido no rótulo
        label->setText(currentNode->getText());

        // Atualiza os textos dos botões com base no nó atual
        leftButton->setText(currentNode->getLeftButtonText());
        rightButton->setText(currentNode->getRightButtonText());

        handleSpecialNode();

        // Desativa os botões se não houver mais escolhas
        if (!currentNode->getLeftChild() && !currentNode->getRightChild()) {
            leftButton->setEnabled(false);
            rightButton->setEnabled(false);

            // Verifica se há um jogador definido no GameData
            GameData *gameData = GameData::getInstance();
            Character* player = gameData->getPlayer();
            if (player) {
                // Usa as informações do jogador na história
                label->setText("Você, " + player->getName() + ", chegou ao final dessa pequena grande história.\nMeus parabéns, outras grandes aventuras estão por vir!");
            }
        } else {
            // Desabilita o botão se estiver no nó correspondente à tela
            rightButton->setEnabled(currentNode->getText() != "(3)");
            leftButton->setEnabled(currentNode->getText() != "(13)");
            rightButton->setEnabled(currentNode->getText() != "(11)");
        }
    }
}

// Tratamento para criação de todas as telas
void DialogWindow::handleSpecialNode()
{
    if (currentNode->getText() == "(1)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/11.png");
        DialogHelper::updateLabel(this, "Ao optar por explorar a clareira, você se aventura por entre as árvores densas da floresta,\nguiado pelo suave murmúrio do vento e pela luz que começa a penetrar as copas das árvores.\nÀ medida que avança, um cenário mágico se revela diante dos seus olhos.\nVocê continua andando e conforme explora a clareira,\npercebe indícios de uma presença mágica.\nFlores que brilham sutilmente, pequenos seres místicos que se escondem entre as folhagens\ne um sentimento de ser observado por algo além do alcance dos olhos.\n\nNesse ponto, suas escolhas ganham um novo significado.\n\nVocê decide:", Qt::AlignTop | Qt::AlignCenter, "color: white;");
        label->show();

    } else if (currentNode->getText() == "(3)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/12.png");
        DialogHelper::updateMovieImage(this, ":/images/assets/monster/ghost/idle.gif");
        DialogHelper::hideChoiceButtons(this);
        acceptGiftButton->show();
        DialogHelper::updateLabel(this, "Ao escolher interagir com as criaturas místicas, o ambiente na clareira\npassa por uma transformação abrupta, com a luz diminuindo e sombras envolvendo o local.\nUma das criaturas, inicialmente imponente, se aproxima lentamente, seu único olho brilhando\ncom uma luz suave que inicialmente causa apreensão.\nContudo, ao se aproximar, a criatura revela-se amigável,\nestendendo uma pequena mão e oferecendo um presente.", Qt::AlignTop | Qt::AlignCenter, "color: white;");

    } else if (currentNode->getText() == "(7)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/11.png");
        npcImgLabel->hide();
        DialogHelper::hideChoiceButtons(this);

    } else if (currentNode->getText() == "(4)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/13.png");
        DialogHelper::updateLabel(this, "Ao investigar o local que um dia abrigou uma fonte mágica,\nme deparei com um espaço vago, um eco silencioso do poder que ali já floresceu.\nA razão para o desaparecimento revelou-se como a consequência de uma antiga batalha\nentre seres místicos, que resultou na extinção da fonte. \n\nDiante do espaço vago que antes abrigava a fonte mágica,\nduas escolhas se apresentavam...\n\nVocê decide:", Qt::AlignTop | Qt::AlignCenter, "color: black;");

    } else if (currentNode->getText() == "(9)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/19.png");
        DialogHelper::hideChoiceButtons(this);

    } else if (currentNode->getText() == "(10)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/11.png");
        DialogHelper::hideChoiceButtons(this);

    } else if (currentNode->getText() == "(2)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/17.png");
        DialogHelper::updateMovieImage(this, ":/images/assets/char/mage/idle.gif");
        DialogHelper::updateLabel(this, "Você se depara com uma imponente figura de um aventureiro, cujo olhar penetrante\nse fixa na à sua esquerda, como se pressentisse um destino de transcendental importância.\nUm silêncio carregado de mistério envolve a atmosfera, e o aventureiro,\ncomo uma sentinela do desconhecido, aguarda como um impasse uma escolha.\n\nAssim, diante do aventureiro desbravador, repousa a decisão iminente.\n\nVocê decide:", Qt::AlignTop | Qt::AlignCenter, "color: black;");

    } else if (currentNode->getText() == "(5)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/22.png");
        npcImgLabel->hide();
        BattleWindow* battleWindow = new BattleWindow(this, "GuerreiroGigante");
        DialogHelper::hideChoiceButtons(this);
        label->hide();
        battleWindow->show();
        DialogHelper::hideChoiceButtons(this);

        GameData* gameData = GameData::getInstance();
        Character* playerCharacter = gameData->getPlayer();

        connect(battleWindow, &BattleWindow::battleFinished, this, [=]() {
            if (playerCharacter->getHealth() <= 0) {
                DialogHelper::updateLabel(this, "O herói, em sua jornada épica, confrontou o destino final.\nSua bravura, embora não coroada pela vitória, deixa uma marca para os\njovens aventureiros no tecido das narrativas.\n\nAssim, a epopeia conclui-se, resumindo-se em coragem diante da adversidade.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
                DialogHelper::hideChoiceButtons(this);
                label->show();
            } else if(playerCharacter->getHealth() > 0) {
                DialogHelper::updateLabel(this, "Na esteira da decisão corajosa, você escolheu seguir na direção indicada pelo aventureiro.\n A imponência do guerreiro que protegia a entrada do castelo erguia-se como\numa barreira formidável.\n\nEntretanto, com determinação e habilidade afiada, você enfrentou o guerreiro\nem um duelo intenso. A batalha, um espetáculo de destreza e coragem, culminou na sua vitória,\na imponência do guerreiro agora um testemunho silencioso das suas proezas.\n\nÀ medida que a poeira assentava, se revelava a entrada de um castelo desprotegido.\n\nVocê decide:", Qt::AlignTop | Qt::AlignCenter, "color: white;");
                label->show();
                DialogHelper::showChoiceButtons(this);
            }
        });

    } else if (currentNode->getText() == "(11)") {

        DialogHelper::updateMovieImage(this, ":/images/assets/char/mage/idle.gif");
        DialogHelper::updateLabel(this, "Chamei o aventureiro ao local onde a batalha havia acontecido, eu o aguardava\ncom olhos ansiosos pela notícia do desfecho.\n\nO sorriso de triunfo estampava meu rosto, enquanto compartilhava\nas boas novas com o companheiro de jornada.\n\nSob o céu anoitecido, encontrei meu refúgio entre sombras das ruínas antigas,\nrendendo-me ao merecido descanso, enquanto os feitos heróicos ecoavam\nsuavemente nos recantos da minha mente, antevendo sonhos repletos de\nnovas jornadas a desvendar ao amanhecer.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
        rightButton->hide();

    } else if (currentNode->getText() == "(17)") {

        DialogHelper::hideChoiceButtons(this);
        npcImgLabel->hide();

    } else if (currentNode->getText() == "(12)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/24.png");
        DialogHelper::updateImageLabel(this, ":/images/assets/item/chest/items.png");
        DialogHelper::hideChoiceButtons(this);
        getItemsButton->show();
        DialogHelper::updateLabel(this, "Ao explorar os corredores do castelo desguarnecido, descobri uma câmara oculta\nrepleta de tesouros, saqueando riquezas acumuladas ao longo de batalhas épicas\ne desafios superados. Cada passo reverberava entre os pilares de pedra,\nenquanto os tesouros, banhados pela luz que se infiltrava sutilmente, revelavam-se\ncomo relíquias ansiosas para contar suas histórias.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
        label->show();

    } else if (currentNode->getText() == "(19)") {

        DialogHelper::hideChoiceButtons(this);

    } else if (currentNode->getText() == "(6)") {

        npcImgLabel->hide();
        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/5.png");
        DialogHelper::updateImageLabel(this, ":/images/assets/group-char.png");
        DialogHelper::updateLabel(this, "Enquanto seguia o caminho próximo ao castelo conquistado por monstros a uma década, você,\num intrépido aventureiro solitário, depara-se com um grupo de seis aventureiros experientes.\nEles estavam reunidos em uma clareira, discutindo os boatos sobre o tesouro lendário\nprotegido pelos monstros no castelo.\n\nIntrigados com a perspectiva de recompensas incríveis, você decide se juntar a eles,\ncompartilhando suas habilidades e conhecimentos para enfrentar o desafio iminente.", Qt::AlignTop | Qt::AlignCenter, "color: black;");
        rightButton->hide();

    } else if (currentNode->getText() == "(13)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/9.png");
        npcImgLabel->hide();
        BattleWindow* battleWindow = new BattleWindow(this, "GrupoDeInimigos");
        DialogHelper::hideChoiceButtons(this);
        label->hide();
        battleWindow->show();
        DialogHelper::hideChoiceButtons(this);

        GameData* gameData = GameData::getInstance();
        Character* playerCharacter = gameData->getPlayer();

        connect(battleWindow, &BattleWindow::battleFinished, this, [=]() {
            if (playerCharacter->getHealth() <= 0) {
                DialogHelper::updateLabel(this, "O grupo de aventureiros percebeu tarde demais que a batalha que se segue é mais intensa\ndo que qualquer um de vocês poderia ter imaginado.\n\nOs monstros, em número e força superiores, impõem uma derrota amarga.\n\nFeridos e desanimados, vocês recuam para a segurança da floresta,\nonde decidem encerrar sua tentativa.", Qt::AlignTop | Qt::AlignCenter, "color: black;");
                DialogHelper::hideChoiceButtons(this);
                label->show();
            } else if(playerCharacter->getHealth() > 0) {
                DialogHelper::updateLabel(this, "A batalha é intensa, mas, desta vez, a cooperação e a estratégia prevalecem.\n\nOs monstros são derrotados, e o castelo se torna um tesouro aberto para vocês.\n\nA alegria e o alívio permeiam o grupo enquanto contam suas conquistas e dividem os espólios.", Qt::AlignTop | Qt::AlignCenter, "color: black;");
                label->show();
                DialogHelper::showChoiceButtons(this);
                leftButton->hide();
            }
        });

    } else if (currentNode->getText() == "(16)") {

        DialogHelper::updateBackground(this, ":/images/assets/backgrounds/23.png");
        DialogHelper::updateImageLabel(this, ":/images/assets/group.png");
        DialogHelper::updateLabel(this, "Com os bolsos cheios de ouro e as mentes repletas de histórias épicas,\no grupo de aventureiros decide celebrar a vitória em seu acampamento.\n\nA notícia se espalha rapidamente pela região, e a comunidade local se une à festa.\nO dia se torna um momento de risos, música e celebração.\n\nÀ medida que a o dia termina, vocês compartilham experiências, criam laços mais fortes\ne percebem que a jornada, apesar das adversidades, valeu a pena.\n\nAssim decidem encerrar a celebração daquele dia, lembrando-se das memórias\ncompartilhadas e dos tesouros conquistados, ansiosos por novas aventuras que o\nfuturo possa trazer.", Qt::AlignTop | Qt::AlignCenter, "color: black;");
        leftButton->hide();

    } else if (currentNode->getText() == "(20)") {

        DialogHelper::hideChoiceButtons(this);
        npcImgLabel->hide();

    }
}

// Botão para aceitar o presente
void DialogWindow::handleAcceptGift()
{
    DialogHelper::updateLabel(this, "Aceitando o presente, percebe-se que as criaturas não eram ameaçadoras,\nmas sim guardiãs da floresta.\nElas compartilham contigo um livro que contém informações grandiosas.\nAgradecendo, a criaturas que veio ao teu encontro desaparece nas sombras,\ndeixando para trás apenas o item dado a você.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
    label->show();
    acceptGiftButton->hide();
    DialogHelper::showChoiceButtons(this);
    DialogHelper::updateImageLabel(this, ":/images/assets/item/41.png");
    rightButton->hide();
}

// Botão para pegar os espólios
void DialogWindow::handleGetItems()
{
    npcImgLabel->hide();
    BattleWindow* battleWindow = new BattleWindow(this, "Mimico");
    DialogHelper::hideChoiceButtons(this);
    label->hide();
    battleWindow->show();
    DialogHelper::hideChoiceButtons(this);
    getItemsButton->hide();

    GameData* gameData = GameData::getInstance();
    Character* playerCharacter = gameData->getPlayer();

    connect(battleWindow, &BattleWindow::battleFinished, this, [=]() {
        if (playerCharacter->getHealth() <= 0) {
            DialogHelper::updateLabel(this, "O herói, em sua jornada épica, confrontou o destino final.\nSua bravura, embora não coroada pela vitória, deixa uma marca para os\njovens aventureiros no tecido das narrativas.\n\nAssim, a epopeia conclui-se, resumindo-se em coragem diante da adversidade.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
            DialogHelper::hideChoiceButtons(this);
            label->show();
        } else if(playerCharacter->getHealth() > 0) {
            DialogHelper::updateLabel(this, "Após derrotar o mimico, a ilusão de uma caixa de loot desvaneceu-se, revelando\nas garras vencidas do monstro dissimulado.\n\nA câmara agora exibia os destroços da batalha, e eu, vitorioso,\ncontemplava o triunfo sobre a astúcia disfarçada em promessas de tesouro.", Qt::AlignTop | Qt::AlignCenter, "color: white;");
            label->show();
            DialogHelper::showChoiceButtons(this);
            leftButton->hide();
        }
    });
}
