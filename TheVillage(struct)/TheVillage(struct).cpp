#include <iostream>
#include <fstream>
#include <string>
#include <vector>

enum roomType {
    living_room,
    bedroom,
    kitchen,
    bathroom,
    toilet,
    children
};
enum buildingType {
    house,
    garage,
    barn,
    bathhouse
};

struct room {
    roomType roomType; // тип комнаты из перечисления
    double roomArea; // площадь комнаты
    double height; // высота потолка
};
struct Floor {
    std::vector<room> rooms; // список комнат на этаже
    double tatalFloorArea; // общая площадь этажа
};
struct building {
    buildingType buildingType; // тип зданий из перечисления
    double area; // площадь которую занимает здание на участке
    bool hasStove; // наличие печи для дома или бани
    std::vector<Floor> floors; // Этажи здание если это дом
};
struct plot {
    int plotNumber; // номер участка
    double totalArea; // общая площадь участк
    std::vector<building> buildings; // список зданий на участке
};
struct village {
    std::vector<plot> plots; //список участков
};



room inputRoom() {
    room room;
    int roomTypeIn;
    std::cout << "Input room type(0-living room, 1-bedroom, 2-kitchen, 3-bathroom, 4-toilet, 5-children): ";
    std::cin >> roomTypeIn;
    room.roomType = static_cast<roomType>(roomTypeIn);

    std::cout << "Enter room area: ";
    std::cin >> room.roomArea;
    std::cout << "Enter room height: ";
    std::cin >> room.height;
    return room;
}
Floor inputFloor() {
    Floor floor;
    int numRooms;
    std::cout << "Enter number of rooms on the floor: ";
    std::cin >> numRooms;

    while (numRooms < 2 || numRooms > 4) {
        std::cerr << "Rooms must be between 2 and 4!Please enter again: " << std::endl;
        std::cin >> numRooms;
    }
    for (int i = 0; i < numRooms; ++i) {
        floor.rooms.push_back(inputRoom());
    }
    return floor;
}
building inputBuilding() {
    building building;
    int buildingTypeIn;
    std::cout << "Input building type 0-house, 1-garage, 2-barn, 3-bathhouse: ";
    std::cin >> buildingTypeIn;
    building.buildingType = static_cast<buildingType>(buildingTypeIn);

    std::cout << "Enter building area: ";
    std::cin >> building.area;
    std::cout << "Does it have a stove? (1 for yes, 0 for no): ";
    std::cin >> building.hasStove;

    if (building.buildingType == house) {
        int numFloors;
        std::cout << "Enter number of floors: ";
        std::cin >> numFloors;

        while (numFloors < 1 || numFloors > 3) {
            std::cerr << "Floors must be between 1 and 3!Please enter again: " << std::endl;
            std::cin >> numFloors;
        }

        for (int i = 0; i < numFloors; ++i) {
            building.floors.push_back(inputFloor());
        }
    }
    return building;
}
plot inputPlot() {
    plot plot;
    std::cout << "Enter plot number: ";
    std::cin >> plot.plotNumber;
    std::cout << "Enter total plot area: ";
    std::cin >> plot.totalArea;

    int numBuildings;
    std::cout << "Enter number of buildings: ";
    std::cin >> numBuildings;
    for (int i = 0; i < numBuildings; ++i) {
        plot.buildings.push_back(inputBuilding());
    }
    return plot;
}
village inputVillage() {
    village village;
    int numPlots;
    std::cout << "Enter number of plots: ";
    std::cin >> numPlots;
    for (int i = 0; i < numPlots; ++i) {
        village.plots.push_back(inputPlot());
    }
    return village;
}

double calculateTotalAreaPercentage(const village& village) {
    double totalPlotArea = 0.0;
    double totalBuildingArea = 0.0;
    for (const auto& plot : village.plots) {
        totalPlotArea += plot.totalArea;
        for (const auto& building : plot.buildings) {
            totalBuildingArea += building.area;
        }
    }
    if (totalPlotArea == 0) return 0.0;
    return (totalBuildingArea / totalPlotArea) * 100.0;
}
int main()
{
    village myVillage = inputVillage();

    double areaPercentage = calculateTotalAreaPercentage(myVillage);

    std::cout << "Percentage of land area occupied by buildings: " << areaPercentage << "%" << std::endl;

    return  0;
}
