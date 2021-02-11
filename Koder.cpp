#include<iostream>
#include<fstream>
#include<iomanip>
#include<cstdlib>
#include<ctime>
#include<cstdio>
using namespace std;

const int ileLiterRazem = 52;

int program();
int blad();
int czyDalej();

//tymczasowo
int koduj(char[], string, char[], int);
int altKoduj(char[], string, char[]);
int dekoduj(string, char[], int);
int altDekoduj(string, char[]);
int zlicz(string);
int decyduj(int);
int usunLinie();

//czas podstawic literki losowo !!
int alph(char[]);
int tabRand(char[], int[]);
int genTab(int[]);
int szukaj(string, int, char[]);
int altSzukaj(string, char[]);
int przekazTab(char[]);

int main()
{
	srand(time(NULL));
	program();
	
	return 0;	
}


int program()
{
	int iloscSpacji;
	int jakDuzo;
	string plik;
	string wybor;
	int tabLiczb[ileLiterRazem];
	char Pod[ileLiterRazem];
	char alfabet[ileLiterRazem];
	
	alph(alfabet);
	alph(Pod);
	genTab(tabLiczb);
	tabRand(Pod, tabLiczb);
	
	cout << "Wybierz operacje (kodowanie, dekodowanie, wyjscie) ";
	cin >> wybor;
	
	if (wybor != "kodowanie" && wybor != "dekodowanie" && wybor != "wyjscie") blad();
	
	if (wybor == "wyjscie") exit(1);
	
	cout << "Podaj nazwe pliku: ";
	cin >> plik;
	
	iloscSpacji = zlicz(plik);
	jakDuzo = decyduj(iloscSpacji);
	
	if (wybor == "kodowanie")
	{
		if (jakDuzo != 0) koduj(Pod, plik, alfabet, jakDuzo);
		else altKoduj(Pod, plik, alfabet);
	}
	
	if (wybor == "dekodowanie")
	{
		if (jakDuzo != 0) dekoduj(plik, alfabet, jakDuzo);
		else altDekoduj(plik, alfabet);
	}
	
	czyDalej();
	
	return 0;
}


int blad()
{
	cout << "Blad" << endl;
	system("pause");
	system("cls");
	program();	
	
	return 0;		
}

int czyDalej()
{
	string wybor;
	cout << endl;
	cout << "Czy chcesz kontynuowac? (tak/nie) ";
	cin >> wybor;
	
	if(wybor == "tak") program();
	else if (wybor == "nie") exit(1);
	else czyDalej();
}

int zlicz(string plik)
{
	int licznik = 0;
	ifstream ifs;
	char c;
	
	ifs.open(plik.c_str(), ios::in);
	
	if(!ifs) blad();
	else
	{
		while(ifs.get(c))
		{
			if (isspace(c))
			{
				licznik++;
			}
		}
	}
	return licznik;
}

int decyduj(int liczba)
{
	if (liczba >= 3000) return 50;
	else if (liczba >= 2000) return 35;
	else if (liczba >= 1200) return 20;
	else if (liczba >= 800) return  12;
	else if (liczba >= 400) return 5;
	else if (liczba >= 200) return 3;
	else if (liczba >= 80) return 1;
	else return 0;
}

int koduj(char Pod[], string plik, char alfabet[], int liczba)
{
	ifstream ifs;
	ofstream ofs;
	int licznik = -1;
	int iterator = 0;
	char c;
	
	ifs.open(plik.c_str(), ios::in);
	
	if(!ifs) blad(); 
	else
	{
		ofs.open("encrypted.txt", ios::out);
		if(!ofs) blad();
		
		while(ifs.get(c))
		{	
			for (int i = 0; i < ileLiterRazem; i++)
			{
				if (c == alfabet[i])
				{
					ofs.put(Pod[i]); 
				}
			}
			if (!isalpha(c) && !isspace(c))
			{
				ofs.put(c);				
			}
			if (isspace(c))
			{
				licznik++;
				ofs.put(c);
				
				if(licznik%liczba == 0 && iterator < ileLiterRazem)
				{
					ofs.put(Pod[iterator]);
					iterator++;
				}
			}
		}
		ifs.close();
		ofs.close();
		
		cout << "Plik zostal pomyslnie zakodowany jako encrypted.txt";
	}
	return 0;
}	


int altKoduj(char Pod[], string plik, char alfabet[])
{
	char c;
	ifstream ifs;
	ofstream ofs;
	
	ifs.open(plik.c_str(), ios::in);
	if (!ifs) blad();
	else
	{		
		ofs.open("encrypted.txt", ios::out);
		if (!ofs) blad();
		
		while(ifs.get(c))
		{
			for (int i = 0; i < ileLiterRazem; i++)
			{
				if (c == alfabet[i])
				{
					ofs.put(Pod[i]); 
				}
			}
			if (!isalpha(c))
			{
				ofs.put(c);				
			}	
		}
		ifs.close();
		ofs.close();
		
		przekazTab(Pod);
		
		cout << "Plik zostal pomyslnie zakodowany jako encrypted.txt";
	}
	return 0;
}


int przekazTab(char Pod[])
{
	fstream fs;
	
	fs.open("encrypted.txt", ios::app);
	if (!fs) blad();
	
	fs.put('\n');
	
	for (int i = 0; i < ileLiterRazem; i++)
	{
		fs.put(Pod[i]);
		if ((i%7 == 0 || i%5 == 0) && i != 0) fs.put(' ');
	}
	fs.close();
	
	return 0;
}


int dekoduj(string plik, char alfabet[], int liczba)
{
	ifstream ifs;
	ofstream ofs;
	int licznik = -1;
	int iterator = 0;
	char c;
	char tabPodstawien[ileLiterRazem];
	
	szukaj(plik, liczba, tabPodstawien);
	
	ifs.open(plik.c_str(), ios::in);
	if(!ifs) blad(); 
	
	else
	{
		ofs.open("decrypted.txt", ios::out);
		if(!ofs) blad();
				
		while(ifs.get(c))
		{
			if (isspace(c))
			{
				licznik++;
				if(licznik%liczba == 0 && iterator < ileLiterRazem)
				{
					ofs.put(c);
					ifs.get(c);
					iterator++;
					continue;
				}
			}
			for (int i = 0; i < ileLiterRazem; i++)
			{
				if (c == tabPodstawien[i])
				{
					ofs.put(alfabet[i]);
				}
			}
			if (!isalpha(c))
			{
				ofs.put(c);
			}
		}
		ifs.close();
		ofs.close();
		cout << "Plik zostal pomyslnie odkodowany jako decrypted.txt";	
	}
	return 0;
}


int szukaj(string plik, int liczba, char tab[])
{
	ifstream ifs;
	int licznik = 0;
	int iterator = 0;
	char c;
	
	ifs.open(plik.c_str(), ios::in);
	if (!ifs) blad();
	
	while(ifs.get(c))
	{
		if (isspace(c))
		{
			if (liczba != 0)
			{
				if (licznik%liczba == 0 && iterator < ileLiterRazem)
				{
					tab[iterator] = ifs.peek();
					iterator++;
				}
			}
			licznik++;
		}
	}
	ifs.close();
	
	return 0;
}

int altDekoduj(string plik, char alf[])
{
	char c;
	char tabPodstawien[ileLiterRazem];	
	ifstream ifs;
	ofstream ofs;
	
	altSzukaj(plik, tabPodstawien);
	
	ifs.open(plik.c_str(), ios::in);
	if (!ifs) blad();
	else
	{
		ofs.open("temp.txt", ios::out);
		if (!ofs) blad();
		
		while(ifs.get(c))
		{
			for (int i = 0; i < ileLiterRazem; i++)
			{
				if (c == tabPodstawien[i])
				{
					ofs.put(alf[i]);
				}
			}
			if (!isalpha(c))
			{
				ofs.put(c);
			}	
		}
		ifs.close();
		ofs.close();
		
		usunLinie();
		remove("temp.txt");
		
		cout << "Plik zostal pomyslnie odkodowany jako decrypted.txt";	
	}
	return 0;
}

int altSzukaj(string plik, char tab[])
{
	char c;
	int licznik = 0;
	string linia;
	int dlugosc = 0;	
	ifstream ifs;
	
	ifs.open(plik.c_str(), ios::ate);
	if(!ifs) blad();
	else
	{
		dlugosc = ifs.tellg();
		
		for(int i = dlugosc-2; i > 0; i--)
		{
			ifs.seekg(i);
			c = ifs.get();
			
			if(c == '\r' || c == '\n') break;
		}
		
		getline(ifs, linia);
		
		for (int i = 0; i < linia.length(); i++)
		{
			if(linia[i] == ' ') continue;
			tab[licznik] = linia[i];
			licznik++;
		}
		ifs.close();
	}

	return 0;	
}

int usunLinie()
{
	ifstream ifs;
	ofstream ofs;
	string line;
	int licznik = 0;
	
	ifs.open("temp.txt");
	if(!ifs) blad();
	ofs.open("decrypted.txt");
	if(!ofs) blad();
	
	for(string tmp; getline(ifs, tmp); line.swap(tmp))
	{
		if (line.length() == 0 && licznik == 0) continue;
		ofs << line << '\n';
		licznik++;
	}
	ifs.close();
	ofs.close();
	return 0;
}

int alph(char tab[])
{
	int j = 0;
	
	for (int i = 65; i <=90; i++)
	{
		tab[j] = char(i);
		++j;
	}
	for (int i = 97; i <= 122; i++)
	{
		tab[j] = char(i);
		++j;	
	}
	return 0;
}

int genTab (int tab[])
{
	for (int i = 0; i < ileLiterRazem; i++)
	{
		bool sprawdzenie;
		int liczba;
		do
		{
			liczba = rand()%ileLiterRazem;
			sprawdzenie = true;
			
			for (int j = 0; j < i; j++)
			{
				if (liczba == tab[j])
				{
					sprawdzenie = false;
					break;
				}
			}
		} while (!sprawdzenie);
		
		tab[i] = liczba;
	}
	return 0;
}


int tabRand(char tabP[], int tabL[])
{
	for (int i = 0; i < ileLiterRazem; i++)
	{
		int temp = tabP[i];
		tabP[i] = tabP[tabL[i]];
		tabP[tabL[i]] = temp;
	}
}







