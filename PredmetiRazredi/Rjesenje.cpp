#include<iostream>
#include<vector>
#include<string>
#include<regex>
using namespace std;
enum Predmeti { Matematika, Historija, Geografia, Hemija, Biologija, Engleski, Muzicko, Fizicko };
enum Razredi { I1, I2, I3, II1, II2, II3, III1, III2, III3, IV1, IV2, IV3 };
const char * ispisPredmeti[] = { "Matematika", "Historija", "Geografia", "Hemija", "Biologija", "Engleski", "Muzicko", "Fizicko" };
const char * ispisRazredi[] = { "I1", "I2", "I3", "II1", "II2", "II3", "III1", "III2", "III3", "IV1", "IV2", "IV3" };
const char *crt = "\n-------------------------------------\n";
ostream &operator<<(ostream &c, const Predmeti p) {
	if (p == Matematika) c << " Matematika ";
	else if (p == Historija) c << " Historija ";
	else if (p == Geografia) c << " Geografija ";
	else if (p == Hemija) c << " hemija ";
	else if (p == Biologija) c << " Biologija ";
	else if (p == Engleski) c << " engleski ";
	else if (p == Muzicko) c << " Muzicko ";
	else if (p == Fizicko) c << " fizicko ";
	return c;

}

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	Kolekcija()
	{
		_elementi1 = nullptr;
		_elementi2 = nullptr;
		_trenutno = 0;
	}
	~Kolekcija()
	{
		delete[]_elementi1;
		delete[]_elementi2;
	}
	//funkcije ->
	Kolekcija(const Kolekcija &k) {
		_elementi1 = new T1[k._trenutno];
		_elementi2 = new T2[k._trenutno];
		_trenutno = k._trenutno;
		for (size_t i = 0; i < k._trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
	}
	Kolekcija &operator=(const Kolekcija &k) {
		if (this == &k) return *this;
		delete[]_elementi1;
		delete[]_elementi2;
		_elementi1 = new T1[k._trenutno];
		_elementi2 = new T2[k._trenutno];
		_trenutno = k._trenutno;
		for (size_t i = 0; i < k._trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
		return *this;
	}
	T1 GetElement1(int index) const { return _elementi1[index]; }
	T2 GetElement2(int index)const { return _elementi2[index]; }
	int GetTrenutno() const { return _trenutno; }
	void AddElement(const T1 &elem1, const T2 &elem2) {

		T1 *temp1 = new T1[_trenutno + 1];
		T2 *temp2 = new T2[_trenutno + 1];
		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		temp1[_trenutno] = elem1;
		temp2[_trenutno] = elem2;
		_elementi1 = temp1;
		_elementi2 = temp2;
		_trenutno++;
	}
	bool RemoveElement(int index) {
		if (index > _trenutno)
			return false;
		for (size_t i = 0; i < _trenutno; i++)
		{
			if (i == index) {
				T1 *temp1 = new T1[_trenutno - 1];
				T2 *temp2 = new T2[_trenutno - 1];
				int _noviniz = 0;
				for (size_t j = 0; j < _trenutno; j++)
				{
					if (i != j) {
						temp1[_noviniz] = _elementi1[j];
						temp2[_noviniz] = _elementi2[j];
						_noviniz++;
					}
				}
				delete[] _elementi1; _elementi1 = nullptr; delete[] _elementi2; _elementi2 = nullptr;
				_elementi1 = temp1; temp1 = nullptr;
				_elementi2 = temp2; temp2 = nullptr;
				_trenutno--;
				return true;
			}
		}
		return false;
	}
	friend ostream &operator<<(ostream &c, const Kolekcija &k) {
		for (size_t i = 0; i < k.GetTrenutno(); i++)
		{
			c << k.GetElement1(i) << " - " << k.GetElement2(i) << endl;
		}
		return c;
	}

};
class Datum {
	int *_dan, *_mjesec, *_godina;
public:
	Datum(int dan = 1, int mjesec = 1, int godina = 2000) {
		_dan = new int(dan);
		_mjesec = new int(mjesec);
		_godina = new int(godina);
	}

	Datum(const Datum&obj) {
		_dan = new int(*obj._dan);
		_mjesec = new int(*obj._mjesec);
		_godina = new int(*obj._godina);
	}

	~Datum() {
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
	}


	friend ostream& operator<< (ostream &COUT, const Datum &obj) {
		COUT << *obj._dan << " " << *obj._mjesec << " " << *obj._godina;
		return COUT;
	}
	//funkcije ->
	Datum &operator=(const Datum &d) {
		if (this == &d) return *this;
		delete _dan; _dan = nullptr;
		delete _mjesec; _mjesec = nullptr;
		delete _godina; _godina = nullptr;
		_dan = new int(*d._dan);
		_mjesec = new int(*d._mjesec);
		_godina = new int(*d._godina);
		return *this;
	}


};
bool ProvjeriValidnostBrojaTelefona(string telefon) {//globalna funkcija
													 /*
													 broj telefona treba biti u formatu: +387(61)-222-333
													 */

	string pravilo("([+]{1})([0-9]{3})([(]{1})([0-9]{2})([)]{1})([-]{1})([0-9]{3})([-]{1})([0-9]{3})");
	if (regex_match(telefon, regex(pravilo)))
		return true;
	return false;

}
class Osoba {
protected:
	char * _imePrezime;
	Datum * _datumRodjenja;
	string _brojTelefona;
public:
	Osoba(const char * imePrezime, Datum datum) {
		_imePrezime = new char[strlen(imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(imePrezime) + 1, imePrezime);
		_datumRodjenja = new Datum(datum);
		_brojTelefona = "";

	}
	Osoba(const Osoba & obj) :_brojTelefona(obj._brojTelefona) {
		_imePrezime = new char[strlen(obj._imePrezime) + 1];
		strcpy_s(_imePrezime, strlen(obj._imePrezime) + 1, obj._imePrezime);
		_datumRodjenja = new Datum(*obj._datumRodjenja);
	}
	virtual ~Osoba() { delete[]_imePrezime; _imePrezime = nullptr; delete _datumRodjenja; _datumRodjenja = nullptr; }

	bool setBrojTelefona(string brojTelefona) {
		if (ProvjeriValidnostBrojaTelefona(brojTelefona)) {
			_brojTelefona = brojTelefona;
			return true;
		}
		return false;
	}
	//funckije ->
	virtual void Info() = 0;
	Osoba &operator=(const Osoba &o) {
		if (this == &o) return *this;
		delete[]_imePrezime; _imePrezime = nullptr; delete _datumRodjenja; _datumRodjenja = nullptr;
		_imePrezime = new char[strlen(o._imePrezime) + 1];
		_datumRodjenja = new Datum(*o._datumRodjenja);
		_brojTelefona = o._brojTelefona;
		return *this;
	}
	bool operator==(const Osoba &o) {
		return strcmp(o._imePrezime, _imePrezime) == 0 && _brojTelefona == o._brojTelefona && _datumRodjenja == o._datumRodjenja;
	}
};

class Nastavnik :public Osoba {
	Kolekcija<Predmeti, Razredi> * _predmetiRazredi;
	int getGodina(Razredi r) {
		if (r >= 0 && r <= 2) return 1;
		else if (r >= 3 && r <= 5) return 2;
		else if (r >= 6 && r <= 8) return 3;
		else if (r >= 9 && r <= 11) return 4;
		return 0;
	}
public:
	Nastavnik(const char *ime, Datum d) :Osoba(ime, d) {
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>();
	}
	Nastavnik(const Nastavnik &n) :Osoba(n) {
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*n._predmetiRazredi);
	}
	~Nastavnik() {
		delete _predmetiRazredi; _predmetiRazredi = nullptr;
	}
	void Info() {}
	bool AddPredmetRazred(Predmeti p, Razredi r) {
		/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I
		NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/

		int brojRazreda = 0;
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == p && getGodina(_predmetiRazredi->GetElement2(i))==getGodina(r))
				return false;
			if (_predmetiRazredi->GetElement1(i) == p)
				brojRazreda++;
		}
		if (brojRazreda > 2)
			return false;
		_predmetiRazredi->AddElement(p, r);
		return true;
	}
	bool RemovePredmetRazred(Predmeti p) {
		for (size_t i = 0; i < _predmetiRazredi->GetTrenutno(); i++)
		{
			if (_predmetiRazredi->GetElement1(i) == p) {
				_predmetiRazredi->RemoveElement(i);
				return true;
			}
		}
		return false;
	}
	bool operator==(const Nastavnik &n) {
		bool isto = false;
		for (size_t i = 0; i < n._predmetiRazredi->GetTrenutno(); i++)
		{
			if (n._predmetiRazredi->GetElement1(i) == _predmetiRazredi->GetElement1(i))
				isto = true;
		}
		if (strcmp(_imePrezime, n._imePrezime) == 0 && _brojTelefona == n._brojTelefona && _datumRodjenja == n._datumRodjenja && isto)
			return true;
		else
			return false;
	}
	Nastavnik &operator=(const Nastavnik &n) {
		if (this == &n) return *this;
		delete _predmetiRazredi; _predmetiRazredi = nullptr;
		Osoba::operator=(n);
		_predmetiRazredi = new Kolekcija<Predmeti, Razredi>(*n._predmetiRazredi);
		return *this;
	}
	Kolekcija<Predmeti, Razredi> &getPredmetiRazredi() { return *_predmetiRazredi; }
	char *getImePrezime() { return _imePrezime; }
};

class Ucenik : public Osoba {
	int _brojUDnevniku;
	Razredi _razred;
	vector<Nastavnik *> _nastavnici;
	Kolekcija<Predmeti, int> _predmetiOcjene;
public:
	Ucenik(const char*ime, Datum d, int brDnevnik, Razredi r) :Osoba(ime, d), _brojUDnevniku(brDnevnik), _razred(r) {}

	void Info() {}
	bool AddNastavnik(Nastavnik &n) {

		/*VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE
		INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET
		*/
		//ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU
		bool PostojiNastavnik = false;
		for (vector<Nastavnik*>::iterator i = _nastavnici.begin(); i < _nastavnici.end(); i++)
		{
			//ako se ovaj nastavnik nalazi vec u ovom razredu, nije potrebno mimo toga provjeravati atribute...Jer se podrazumijeva da predaje neki predmet u tom razredu.
			for (size_t j = 0; j < (*i)->getPredmetiRazredi().GetTrenutno(); j++)
			{
				if ((*i)->getPredmetiRazredi().GetElement2(j) == _razred)
				{
					PostojiNastavnik = true;
				}
			}
		}
		if (!PostojiNastavnik) {
			_nastavnici.push_back(&n);
			return true;
		}
		return false;
	}
	bool AddPredmetOcjenu(Predmeti p, int ocjena) {

		for (vector<Nastavnik*>::iterator i = _nastavnici.begin(); i < _nastavnici.end(); i++)
		{
			for (size_t j = 0; j < (*i)->getPredmetiRazredi().GetTrenutno(); j++)
			{
				if ((*i)->getPredmetiRazredi().GetElement1(j) == p)
				{
					//znaci ovaj nastavnik predaje ovom uceniku
					_predmetiOcjene.AddElement(p, ocjena);
					return true;
				}
			}
		}
		return false;
	}
	vector<Nastavnik*>  &getNastavnici() { return _nastavnici; }
	Kolekcija<Predmeti, int> &getPredmetiOcjene() { return _predmetiOcjene; }
	float GetProsjekByNastavnik(const char *imeNastavnika) {

		float prosjek = 0; int brojac = 0;
		for (vector<Nastavnik*>::iterator i = _nastavnici.begin(); i < _nastavnici.end(); i++)
		{
			if (strcmp((*i)->getImePrezime(), imeNastavnika) == 0) {
				for (size_t j = 0; j < _predmetiOcjene.GetTrenutno(); j++)
				{
					for (size_t k = 0; k < (*i)->getPredmetiRazredi().GetTrenutno(); k++)
					{
						if ((*i)->getPredmetiRazredi().GetElement1(k) == _predmetiOcjene.GetElement1(j)) {
							prosjek += _predmetiOcjene.GetElement2(k);
							brojac++;
						}
					}
				}
			}
		}
		if (brojac == 0 || prosjek == 0) return 0;
		prosjek /= brojac;
		return prosjek;
	}
	friend ostream &operator<<(ostream &c, const Ucenik &u) {
		c << "Ime prezime -> " << u._imePrezime << endl << " Broj indeksa -> " << u._brojUDnevniku << endl << " Broj tel -> " << u._brojTelefona << endl << " Datum rodjenja -> " << *u._datumRodjenja << endl;
		for (size_t i = 0; i < u._predmetiOcjene.GetTrenutno(); i++)
		{
			c << "predmet : " << u._predmetiOcjene.GetElement1(i) << " - ocjena : " << u._predmetiOcjene.GetElement2(i) << endl;
		}
		return c;
	}
};


void main() {

	/****************************************************************************
	1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
	2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA
	   KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
	3. SPASAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URADJENOG ZADATKA
	4. PROGRAMSKI CODE SE TAKODJER NALAZI U FAJLU CODE_.TXT
	5. NAZIV I LISTA PARAMETARA FUNKCIJA MORAJU BITI IDENTIÈNI ONIMA KOJI SU
	   KORIŠTENI U TESTNOM CODE-U.
	6. NIJE POTREBNO BACATI IZUZETKE. SVE FUNKCIJE VRACAJU TRUE ILI FALSE
	****************************************************************************/

#pragma region TestiranjeDatuma
	Datum danas(26, 11, 2015);
	Datum sutra(danas);
	Datum prekosutra;
	prekosutra = danas;
	cout << danas << endl << sutra << endl << prekosutra << crt;
#pragma endregion
#pragma region TestiranjeKolekcije
	Kolekcija<int, int> kolekcija1;
	int brojElemenata = 15;
	for (size_t i = 0; i < brojElemenata; i++)
		kolekcija1.AddElement(i, i);
	cout << kolekcija1 << endl;
	cout << "Trenutna kolekcija ima -> " << kolekcija1.GetTrenutno() << " elemenata. " << endl;
	cout << kolekcija1.GetElement1(9) << " " << kolekcija1.GetElement2(7) << crt << endl;
	kolekcija1.RemoveElement(2);//uklanja element na osnovu lokacije
	cout << crt;

	cout << kolekcija1 << endl << "Brojevi na trazenim lokacijama -> " << endl;//provjera
	cout << kolekcija1.GetElement1(9) << " " << kolekcija1.GetElement2(7) << crt << endl;
	cout << kolekcija1 << endl;
	cout << "Nova kolekcija ima -> " << kolekcija1.GetTrenutno() << " elemenata. " << endl;
	Kolekcija<int, int> kolekcija2;
	kolekcija2 = kolekcija1;
	cout << kolekcija2 << crt;
	if (kolekcija1.GetTrenutno() == kolekcija2.GetTrenutno())
		cout << "ISTI BROJ ELEMENATA" << endl;
	Kolekcija<int, int> kolekcija3(kolekcija2);
	cout << kolekcija3 << crt;
#pragma endregion
#pragma region TestiranjeNastavnika
	Nastavnik jasmin("Jasmin Azemovic", Datum(15, 2, 1980));
	Nastavnik adel("Adel Handzic", Datum(15, 10, 1981));

	/*NASTAVNIK MOZE PREDAVATI ISTI PREDMET, ALI TO MORA BITI U RAZLICITIM ODJELJENJIMA I
	NAJVISE U DVA RAZREDA (NA DVIJE RAZLICITE GODINE)*/

	if (jasmin.AddPredmetRazred(Matematika, I1))
		cout << "Predmeti dodan" << endl;
	if (jasmin.AddPredmetRazred(Historija, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I1))
		cout << "Predmeti dodan" << endl;

	if (jasmin.AddPredmetRazred(Geografia, I2))
		cout << "Predmeti dodan" << endl;

	if (adel.AddPredmetRazred(Historija, III1))
		cout << "Predmeti dodan" << endl;

	if (adel.RemovePredmetRazred(Historija))
		cout << "Predmet uklonjen!" << endl;

	Nastavnik goran(adel);
	if (goran == adel)
		cout << "Nastavnici identicni" << endl;
	goran = jasmin;
	if (goran == jasmin)
		cout << "Nastavnici identicni" << endl;

	Kolekcija<Predmeti, Razredi> & predmetiRazredi = jasmin.getPredmetiRazredi();

	if (!jasmin.setBrojTelefona("+38761111222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (!jasmin.setBrojTelefona("+387-61-111-222"))
		cout << "Broj telefona nije dodan!" << endl;
	if (jasmin.setBrojTelefona("+387(61)-111-222"))
		cout << "Broj telefona uspjesno dodan!" << endl;
#pragma endregion

#pragma region TestiranjeUcenika
	Ucenik denis("Denis Music", Datum(8, 10, 1990), 3, III1);
	Ucenik elmin("Elmin Sudic", Datum(15, 6, 1993), 1, I1);
	Ucenik adil("Adil Joldic", Datum(13, 8, 1992), 2, II1);
	/*
	VODITI RACUNA DA SE DODAJU REFERENCE NA NASTAVNIKE KAKO BI SVI UCENICI DIJELILI ISTE
	INFORMACIJE O NASTAVNICIMA U SLUCAJU DA SE NASTAVNIKU DODA NEKI PREDMET
	*/

	//ZA USPJESNO DODAVANJE, NASTAVNIK MORA POSJEDOVATI (PREDAVATI) NAJMANJE JEDAN PREDMET U TOM RAZREDU

	if (denis.AddNastavnik(jasmin))
		cout << "Nastavnik uspjesno dodan" << endl;
	//ONEMOGUCITI DODAVANJE ISTIH NASTAVNIKA; POJAM ISTI PODRAZUMIJEVA IDENTICNE VRIJEDNOSTI SVIH ATRIBUTA
	if (denis.AddNastavnik(adel))
		cout << "Nastavnik uspjesno dodan" << endl;
	//DA BI SE DODALA OCJENA ZA ODREDJENI PREDMET UCENIK MORA POSJEDOVATI NASTAVNIKA KOJI PREDAJE TAJ PREDMET
	if (denis.AddPredmetOcjenu(Matematika, 3))
		cout << "Ocjena uspjesno dodana" << endl;
	if (denis.AddPredmetOcjenu(Historija, 4))
		cout << "Ocjena uspjesno dodana" << endl;

	vector<Nastavnik*> & nastavnici = denis.getNastavnici();
	cout << "Ucenik Denis ima dodijeljena " << nastavnici.size() << " nastavnika" << endl;

	Kolekcija<Predmeti, int> & uspjeh = denis.getPredmetiOcjene();
	cout << "Denis ima " << uspjeh.GetTrenutno() << " polozenih predmeta" << endl;
	cout << "Prosjecna ocjena kod nastavnika Jasmin Azemovic je " << denis.GetProsjekByNastavnik("Jasmin Azemovic") << endl;

	Ucenik denis2(denis);
	cout << denis2 << endl;

#pragma endregion
	system("pause");
}
