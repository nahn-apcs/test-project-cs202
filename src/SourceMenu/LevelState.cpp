#include <LevelState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <LevelManager.hpp>
#include <BGNode.hpp>
#include <TextNode.hpp>
#include <LevelManager.hpp>



LevelState::LevelState(StateStack& stack, Context context) : State(stack, context), mGUIContainer(GUI::Container::LeftRight) {

    // Tạo SceneGraph
    for (std::size_t i = 0; i < LayerCount; ++i) {
        auto layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    // Tạo Background
    std::unique_ptr<BGNode> mBGNode;
    std::vector<sf::Sprite> backgrounds = {
        sf::Sprite(context.textures->get(Textures::LevelBG))
    };
    mBGNode = std::make_unique<BGNode>(backgrounds);
    mSceneLayers[Background]->attachChild(std::move(mBGNode));


    // Tao text
    std::unique_ptr<TextNode> mTextNode;
    sf::Text LevelText;

    LevelText.setFont(context.fonts->get(Fonts::Main));
    LevelText.setString("Choose Your Level");
    LevelText.setCharacterSize(50);
    LevelText.setFillColor(sf::Color(255, 255, 255, 255));
    LevelText.setOrigin(LevelText.getLocalBounds().width / 2.0f, LevelText.getLocalBounds().height / 2.0f);
    LevelText.setPosition(640, 100);


    mTextNode = std::make_unique<TextNode>(LevelText);
    mSceneLayers[Text]->attachChild(std::move(mTextNode));


    auto level1Button = std::make_shared<GUI::Button>(context, Textures::LevelMap_1, 200, 260);
    level1Button->setPosition(40, 223);
    level1Button->setCallback([this]() {
        LevelManager::getInstance().setCurLevel(LevelManager::Level::Level1);
        //requestStackPop();
        requestStackPush(States::TransitionGame);
        std::cout << "Level 1 button pressed" << std::endl;
        });
    level1Button->setOpen(LevelManager::getInstance().getLevels(0));
    sf::Sprite lock(context.textures->get(Textures::LevelLock));
    lock.setPosition(40, 303);
    mLock.push_back(lock);



    auto level2Button = std::make_shared<GUI::Button>(context, Textures::LevelMap_2, 200, 260);
    level2Button->setPosition(290, 223);
    level2Button->setCallback([this]() {
        //requestStackPop();
        LevelManager::getInstance().setCurLevel(LevelManager::Level::Level2);
        requestStackPush(States::TransitionGame);
        std::cout << "Level 2 button pressed" << std::endl;
        });
    level2Button->setOpen(LevelManager::getInstance().getLevels(1));
    lock.setPosition(290, 303);
    mLock.push_back(lock);

    auto level3Button = std::make_shared<GUI::Button>(context, Textures::LevelMap_3, 200, 260);
    level3Button->setPosition(540, 223);
    level3Button->setCallback([this]() {
        //requestStackPop();
        LevelManager::getInstance().setCurLevel(LevelManager::Level::Level3);
        requestStackPush(States::TransitionGame);
        std::cout << "Level 3 button pressed" << std::endl;
        });
    level3Button->setOpen(LevelManager::getInstance().getLevels(2));
    lock.setPosition(540, 303);
    mLock.push_back(lock);

    auto level4Button = std::make_shared<GUI::Button>(context, Textures::LevelMap_4, 200, 265);
    level4Button->setPosition(790, 223);
    level4Button->setCallback([this]() {
        //requestStackPop();
        LevelManager::getInstance().setCurLevel(LevelManager::Level::Level4);
        requestStackPush(States::TransitionGame);
        std::cout << "Level 4 button pressed" << std::endl;
        });
    level4Button->setOpen(LevelManager::getInstance().getLevels(3));
    lock.setPosition(790, 303);
    mLock.push_back(lock);

    auto level5Button = std::make_shared<GUI::Button>(context, Textures::LevelMap_5, 200, 265);
    level5Button->setPosition(1040, 216);
    level5Button->setCallback([this]() {
        //requestStackPop();
        LevelManager::getInstance().setCurLevel(LevelManager::Level::Level5);
        requestStackPush(States::TransitionGame);
        std::cout << "Level 5 button pressed" << std::endl;
        });
    level5Button->setOpen(LevelManager::getInstance().getLevels(4));
    lock.setPosition(1040, 303);
    mLock.push_back(lock);


    mGUIContainer.pack(level1Button);
    mGUIContainer.pack(level2Button);
    mGUIContainer.pack(level3Button);
    mGUIContainer.pack(level4Button);
    mGUIContainer.pack(level5Button);


    mBackButton.setTexture(context.textures->get(Textures::LevelBackButton));
    mBackButton.setTextureRect(sf::IntRect(0, 0, 100, 35));
    mBackButton.setPosition(0, 605);

    sf::Sprite pointer;
    pointer.setTexture(context.textures->get(Textures::LevelPointer1));
    pointer.setPosition(50, 503);
    mPointer.push_back(pointer);

    sf::Sprite pointer_1;
    pointer_1.setTexture(context.textures->get(Textures::LevelPointer2));
    pointer_1.setPosition(340, 503);
    mPointer.push_back(pointer_1);

    sf::Sprite pointer_2;
    pointer_2.setTexture(context.textures->get(Textures::LevelPointer3));
    pointer_2.setPosition(608, 493);
    mPointer.push_back(pointer_2);

    sf::Sprite pointer_3;
    pointer_3.setTexture(context.textures->get(Textures::LevelPointer4));
    pointer_3.setPosition(847, 498);
    mPointer.push_back(pointer_3);

    sf::Sprite pointer_4;
    pointer_4.setTexture(context.textures->get(Textures::LevelPointer5));
    pointer_4.setPosition(1107, 503);
    mPointer.push_back(pointer_4);


}

void LevelState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());

    window.draw(mSceneGraph);

    window.draw(mBackButton);


    window.draw(mGUIContainer);

    for (int i = 0; i < 5; i++) {
        if (!LevelManager::getInstance().getLevels(i)) {
            window.draw(mLock[i]);
        }
    }

    window.draw(mPointer[mGUIContainer.getSelectedChild()]);


}

bool LevelState::update(sf::Time deltatime)
{
    for (int i = 0; i < 5; i++) {
        if (LevelManager::getInstance().getLevels(i)) {
            mGUIContainer.setOpen(i, true);
        }
        else {
            mGUIContainer.setOpen(i, false);
        }
    }

    // Command để scale chữ
    Command scaleTextCommand;
    scaleTextCommand.category = Category::Text;
    scaleTextCommand.action = [deltatime](SceneNode& node, sf::Time) {
        auto& textNode = static_cast<TextNode&>(node);
        textNode.updateTime(deltatime);
        float scale = 1 + 0.03f * std::sin(textNode.getElapsedTime() * 7.0f);
        textNode.setScale(scale);
        };

    // Đẩy Command vào CommandQueue
    mCommandQueue.push(scaleTextCommand);

    while (!mCommandQueue.isEmpty()) {
        Command command = mCommandQueue.pop();
        mSceneGraph.onCommand(command, deltatime);
    }



    // Cập nhật SceneGraph
    mSceneGraph.update(deltatime, mCommandQueue);




    return false;
}

bool LevelState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);

    if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
            if (mBackButton.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
                requestStackPop();
            }
        }
    }
    else if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::Escape) {
            requestStackPop();
        }
    }
    return false;
}