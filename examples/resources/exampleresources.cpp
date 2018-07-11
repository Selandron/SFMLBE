#include "../../release/sfmlbe.hpp"
#include "../../release/tinyxml2.hpp"

/*

    EXAMPLE : HOW TO USE THE RESOURCE MANAGER

    This example show how to use the Resource Manager in real condition.
    For further explanations of how to load the resources see the benchmarkresourcesexample.cpp file.

    The ResourceManager is a Singleton templated thread-safe class, which mean that you can call the only existing instance of the class using sfmlbe::ResourceManager::GetInstance() from anywhere in your program.
    But be careful ! The resource manager load and unload resources, but if you unload resources still used you program will crash. 

    In this example you will see how to retreive loaded resources and how to use them. It is really easy, you juste have to call the Macro functions.

    How to compile :
    Go in the example folder and use :
    g++ .\resources\exampleresources.cpp ..\release\sfmlbe.cpp ..\release\tinyxml2.cpp -W -Wall -ansi -std=c++11 -I"SFMLPATH"\include -L"SFMLPATH"\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o exe
    Don't forget to add .dll on Windows !

 */

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Resources");

    //Load the resources, the first scope of the benchmark file
    sfmlbe::ResourceManager * resMan = sfmlbe::ResourceManager::GetInstance();
    resMan->LoadFromFileXML("benchmark.xml");
    resMan->PrintManager();

    sf::Sprite sprite;
    sf::Music * music;
    sf::Texture texture;
    sf::Font font;
    sf::SoundBuffer buffer;
    sf::Sound sound;
    sf::Text text;
    std::string string;

    //Always use a try catch when you call the resources !
    try
    {
    	texture = *_GET_TEXTURE("wood_tileset");
    	font = *_GET_FONT("arial");
    	string = *_GET_TEXT("text1", "first-key");
    	music = _GET_MUSIC("power-bots-loop"); //Music can be copied, you have to use referencs only
    	buffer = *_GET_SOUNDBUFFER("patakas-world");
    }
    catch(sfmlbe::ResourceNotFoundException e)
    {
    	std::cout << e.what() << std::endl;
    }
    //Set the resources
    text.setFont(font);
    text.setString(string);
    sprite.setTexture(texture);
    sound.setBuffer(buffer);
    sound.play();
    music->play();
    	

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(sprite);
        window.draw(text);

        window.display();
    }

    resMan->Clear();
    sfmlbe::ResourceManager::Kill();
	return 0;
}