#include <MenuState.hpp>
#include <Button.hpp>
#include <Utility.hpp>
#include <ResourceHolder.hpp>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/View.hpp>
#include <iostream>
#include <SFML/System/Time.hpp>
#include <TextNode.hpp>
#include <BGNode.hpp>
#include <BGObject.hpp>
#include <LevelManager.hpp>


MenuState::MenuState(StateStack& stack, Context context) : State(stack, context), mGUIContainer(GUI::Container::TopDown) {

    // Tạo SceneGraph
    for (std::size_t i = 0; i < LayerCount; ++i) {
        auto layer = std::make_unique<SceneNode>();
        mSceneLayers[i] = layer.get();
        mSceneGraph.attachChild(std::move(layer));
    }

    std::unique_ptr<BGNode> mBGNode;

    std::vector<sf::Sprite> backgrounds = {
        sf::Sprite(context.textures->get(Textures::MainMenuBG_1)),
        sf::Sprite(context.textures->get(Textures::MainMenuBG_2)),
        sf::Sprite(context.textures->get(Textures::MainMenuBG_3))
    };
    mBGNode = std::make_unique<BGNode>(backgrounds);

    // Gắn BGNode vào lớp nền của SceneGraph
    mSceneLayers[Background]->attachChild(std::move(mBGNode));

    // Tạo BGObject cho đám mây
    std::unique_ptr<BGObject> mCloudBGObject;

    // Tạo danh sách sprite cho đám mây
    std::vector<sf::Sprite> cloudSprites;
    std::vector<float> cloudSpeeds = { 60, 60, 75, 75, 75, 90, 90, 90 };

    sf::Sprite tmp;

    // Thêm các sprite vào vector
    sf::Texture& texture_1 = context.textures->get(Textures::MainMenuClound_8);
    tmp = sf::Sprite(texture_1);
    tmp.setPosition(759, -9);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_2 = context.textures->get(Textures::MainMenuClound_7);
    tmp = sf::Sprite(texture_2);
    tmp.setPosition(345, -9);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_3 = context.textures->get(Textures::MainMenuClound_6);
    tmp = sf::Sprite(texture_3);
    tmp.setPosition(897, 0);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_4 = context.textures->get(Textures::MainMenuClound_5);
    tmp = sf::Sprite(texture_4);
    tmp.setPosition(449, 3);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_5 = context.textures->get(Textures::MainMenuClound_4);
    tmp = sf::Sprite(texture_5);
    tmp.setPosition(0, 10);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_6 = context.textures->get(Textures::MainMenuClound_3);
    tmp = sf::Sprite(texture_6);
    tmp.setPosition(950, 37);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_7 = context.textures->get(Textures::MainMenuClound_2);
    tmp = sf::Sprite(texture_7);
    tmp.setPosition(475, 48);
    cloudSprites.push_back(tmp);

    sf::Texture& texture_8 = context.textures->get(Textures::MainMenuClound_1);
    tmp = sf::Sprite(texture_8);
    tmp.setPosition(0, 37);
    cloudSprites.push_back(tmp);

    // Tạo BGObject cho đám mây
    mCloudBGObject = std::make_unique<BGObject>(cloudSprites, cloudSpeeds);

    // Gắn BGObject vào lớp SceneGraph
    mSceneLayers[Cloud]->attachChild(std::move(mCloudBGObject));





    auto playButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
    playButton->setPosition(565, 340);
    playButton->setText("Play");
    playButton->setCallback([this]() {
        //requestStackPop();
        requestStackPush(States::Level);
        std::cout << "Play button pressed" << std::endl;
        });

    auto ContinueButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
    ContinueButton->setPosition(565, 400);
    ContinueButton->setText("Continue");
    ContinueButton->setCallback([this]() {
		//requestStackPop();
		requestStackPush(States::Level);
        requestStackPush(States::TransitionGame);
        LevelManager::getInstance().setCurLevel(LevelManager::None);
		std::cout << "Continue button pressed" << std::endl;
		});

    auto guideButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
    guideButton->setPosition(565, 460);
    guideButton->setText("Guide");
    guideButton->setCallback([this]() {
        //requestStackPop();
        requestStackPush(States::Guide);
        std::cout << "Guide button pressed" << std::endl;
        });


    auto settingButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
    settingButton->setPosition(565, 520);
    settingButton->setText("Setting");
    settingButton->setCallback([this]() {
        //requestStackPop();
        requestStackPush(States::Setting);
        std::cout << "Setting button pressed" << std::endl;
        });

    auto exitButton = std::make_shared<GUI::Button>(context, Textures::button, 150, 45);
    exitButton->setPosition(565, 580);
    exitButton->setText("Quit");
    exitButton->setCallback([this]() {
        requestStackPop();
        });

    mGUIContainer.pack(playButton);
    mGUIContainer.pack(ContinueButton);
    mGUIContainer.pack(guideButton);
    mGUIContainer.pack(settingButton);
    mGUIContainer.pack(exitButton);

    // Thêm Game Name (TextNode)
    sf::Font& font = context.fonts->get(Fonts::NameGame);
    sf::Text text;
    text.setFont(font);
    text.setString("Journey to the West");
    text.setCharacterSize(120);
    text.setFillColor(sf::Color::Black);
    text.setOrigin(text.getLocalBounds().width / 2.f, text.getLocalBounds().height / 2.f);
    text.setPosition(640.f, 150.f);

    sf::Text shadowText = text;
    shadowText.setFillColor(sf::Color(0, 0, 0, 128));
    shadowText.setPosition(text.getPosition().x + 5, text.getPosition().y + 5);

    auto textNode = std::make_unique<TextNode>(text, shadowText);
    mSceneLayers[GameName]->attachChild(std::move(textNode));

}

void MenuState::draw() {
    sf::RenderWindow& window = *getContext().window;
    window.setView(window.getDefaultView());


    // Vẽ toàn bộ SceneGraph
    window.draw(mSceneGraph);

    window.draw(mGUIContainer);
}

bool MenuState::update(sf::Time deltatime)
{

    // Command để scale chữ
    Command scaleTextCommand;
    scaleTextCommand.category = Category::Text;
    scaleTextCommand.action = [deltatime](SceneNode& node, sf::Time) {
        auto& textNode = static_cast<TextNode&>(node);
        float scaleSpeed = 0.5f * deltatime.asSeconds();
        float currentScale = textNode.getScale();

        if (currentScale < 1.0f) {
            float scale = currentScale + scaleSpeed;
            scale = std::min(scale, 1.0f);
            textNode.setScale(scale);
        }
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

bool MenuState::handleEvent(const sf::Event& event)
{
    mGUIContainer.handleEvent(event);
    return false;
}