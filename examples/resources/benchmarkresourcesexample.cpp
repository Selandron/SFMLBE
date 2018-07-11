#include "../../release/sfmlbe.hpp"
#include "../../release/tinyxml2.hpp"

/*

    EXAMPLE : HOW TO BENCHMARK THE RESOURCE MANAGER

    This example show how to use the loading part of the Resource Manager system.
    For further explanations of how to use the resources see the exampleresources.cpp file.

    The ResourceManager is a Singleton templated thread-safe class, which mean that you can call the only existing instance of the class using sfmlbe::ResourceManager::GetInstance() from anywhere in your program.
    But be careful ! The resource manager load and unload resources, but if you unload resources still used you program will crash. 

    In this example, you will see how to load and unload an xml indexer.
    An indexer is used to register all paths to the resources files (i.e. textures, sounds, etc..). All indexers are searched in the data folder next to the binary, and all the resources are also searched in data.
    In this indexer you have to define one or more scopes. In this scope you can define the pathes to the resources. 
    If a tag isn't named 'file', it is considered as a folder and resources will be searched inside. If a tag is named 'file', it is considered as a resource and need a number tyoe (see RESOURCE_TYPE), a key to be found in the scope and a valide name inside the tag.

    It is highly recommended to see the benchmark.xml file for good examples !

    Scopes can be loaded and unloaded easily using the LoadFromFileXML function.
    By default, the first valid scope in the file is used, but you can specify a targeted scope.
    You can also specify a loaded (or not) scope where to append the resources.
    See the benchResources function just below to understand all the posibilities of the Resource Manager System.

    How to compile :
    Go in the example folder and use :
    g++ .\resources\benchmarkresourcesexample.cpp ..\release\sfmlbe.cpp ..\release\tinyxml2.cpp -W -Wall -ansi -std=c++11 -I"SFMLPATH"\include -L"SFMLPATH"\lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -o exe
    Don't forget to add .dll on Windows !

 */

void benchResources()
{
    //Get the instance of the Resource Manager
	sfmlbe::ResourceManager * resMan = sfmlbe::ResourceManager::GetInstance();

	//STEP 1 -- LOAD BENCHMARK1 -- SHOULD WORK (result : scope benchmark1 loaded)
    std::cout << "STEP 1 -- LOAD BENCHMARK1 -- SHOULD WORK (result : scope benchmark1 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 2 -- UNLOAD BENCHMARK1 -- SHOULD WORK (result : no resources)
    std::cout << "STEP 2 -- UNLOAD BENCHMARK1 -- SHOULD WORK (result : no resources)" << std::endl;
    resMan->Clear();
    resMan->PrintManager();
    std::cout << std::endl; 

    //STEP 3 -- LOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark2 loaded)
    std::cout << "STEP 3 -- LOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark2 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark2");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 4 -- LOAD TWO SCOPE -- SHOULD WORK (result : scope benchmark1 & benchmark2 loaded)
    std::cout << "STEP 4 -- LOAD TWO SCOPE -- SHOULD WORK (result : scope benchmark1 & benchmark2 loaded)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark1");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 5 -- UNLOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark1 loaded)
    std::cout << "STEP 5 -- UNLOAD BENCHMARK2 -- SHOULD WORK (result : scope benchmark1 loaded)" << std::endl;
    resMan->ClearScope("benchmark2");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 6 -- LOAD BENCHMARK3 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded whithout the errored files)
    std::cout << "STEP 6 -- LOAD BENCHMARK3 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded whithout the errored files)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark3");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 7 -- LOAD BENCHMARK4 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 4)
    std::cout << "STEP 7 -- LOAD BENCHMARK4 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 4)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark4");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 8 -- LOAD BENCHMARK5 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 5)
    std::cout << "STEP 8 -- LOAD BENCHMARK5 -- SHOULD WORK BUT WITH FAILURES (result : scope benchmark1 & 3 loaded but not 5)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark5");
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 9 -- UNLOAD ALL -- SHOULD WORK (result : no resources)
    std::cout << "STEP 9 -- UNLOAD ALL -- SHOULD WORK (result : no resources)" << std::endl;
    resMan->Clear();
    resMan->PrintManager();
    std::cout << std::endl;

    //STEP 10 -- APPEND -- SHOULD WORK (result : benchmark6 & 7 loaded in scope benchmark6)
    std::cout << "STEP 10 -- UNLOAD ALL -- SHOULD WORK (result : no resources)" << std::endl;
    resMan->LoadFromFileXML("benchmark.xml", "benchmark6");
    resMan->LoadFromFileXML("benchmark.xml", "benchmark7", "benchmark6");
    resMan->PrintManager();
    resMan->Clear();
    std::cout << std::endl;

    //Kill the instance of the Resource Manager
    resMan->Kill();
}

int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 600), "Resources");

    //Bench the resource system
    benchResources();

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.display();
    }
	return 0;
}