#include <iostream>
#include <vector>

using namespace std;

struct Panel {
	Panel(){}
	Panel(int l, int w){
		sides.first = l;
		sides.second = w;
		area = (l + w) * 2;
	}
	
	pair<int, int> sides;
	int area;
};

// Если объём не делится нацело на одну из сторон панели, панель не подходит
bool isPanelFit(Panel *panel, int volume){
	if ((volume % panel->sides.first == 0) && (volume % panel->sides.second == 0)){
		return true;
	}
	return false;
}

bool CheckPanelSides(Panel *panel, int length, int width){
	if ((panel->sides.first == length && panel->sides.second == width) ||
		(panel->sides.second == length && panel->sides.first == width)){
		return true;
	}
	return false;
}

int main() {
	cout << "This is the box factory\nPlease input number of panels: ";
	int pCount;
	cin >> pCount;
	
	// Выделим память для массива досок
	Panel *panels = (Panel*)malloc(pCount * sizeof(*panels));
	
	// Запишем в память конфигурации досок
	int length, width;
	for (int i = 0; i < pCount; i++){
		cout << "Please input panel parameters:\n";
		cout << "	length = ";
		cin >> length;
		cout << "	width = ";
		cin >> width;
		panels[i] = Panel(length, width);
	}
	
	// Запишем в память требуемый объём коробки
	cout << "Please input volume of the box: ";
	int volume;
	cin >> volume;
	
	// Соберём в отдельный массив указатели на доски подходящего размера
	vector<Panel*> pVect;
	for (int i = 0; i < pCount; i++){
		if (isPanelFit(&(panels[i]), volume)){
			pVect.push_back(&(panels[i]));
		}
	}
	
	// Проверим возможные комбинации досок и найдём комбинацию с минимальной площадью
	int minTotArea = INT_MAX;
	pair<bool, bool> foundPanels;
	bool foudBoxes = false;
	Panel **box = (Panel**)malloc(3 * sizeof(box));
	Panel **goodBox = (Panel**)malloc(3 * sizeof(box));
	for (Panel *panel : pVect){
		int thSide = (volume / panel->sides.first) / panel->sides.second;
		box[0] = panel;
		for (Panel *nPanel : pVect){
			if (CheckPanelSides(nPanel, thSide, panel->sides.first)){
				foundPanels.first = true;
				box[1] = nPanel;
			}
			if (CheckPanelSides(nPanel, thSide, panel->sides.second)){
				foundPanels.second = true;
				box[2] = nPanel;
			}
		}
		
		if (foundPanels.first && foundPanels.second){
			int totArea = box[0]->area + box[1]->area + box[2]->area;
			cout << "totArea = " << totArea << "\n";
			cout << "MinTotArea = " << minTotArea << "\n";
			if (totArea < minTotArea){
				foudBoxes = true;
				minTotArea = totArea;
				for (int i = 0; i < 3; i++){
					goodBox[i] = box[i];
				}
			}
		}else{
			foundPanels.first = false;
			foundPanels.second = false;
		}
	}
	
	if (foudBoxes){
		cout << "Have the solution\n";
		cout << "area = " << minTotArea << "\n";
		cout << "	(";
		for (int i = 0; i < 3; i++){
			cout << "(" << goodBox[i]->sides.first << ", " << goodBox[i]->sides.second << ")";
		}
		cout << ")\n";
	}else{
		cout << "No solution for this box size with this panels set\n";
	}
	
	cin.get();
	return 0;
}
