#include<iostream>
#include<string>
#include<sstream>
#include<vector>
#include<thread>
#include<mutex>
using namespace std;

/****************************************************************************
1. SVE KLASE TREBAJU POSJEDOVATI ADEKVATAN DESTRUKTOR
2. NAMJERNO IZOSTAVLJANJE KOMPLETNIH I/ILI POJEDINIH DIJELOVA DESTRUKTORA KOJI UZROKUJU RUNTIME ERROR CE BITI OZNACENO KAO "RE"
3. SPAŠAVAJTE PROJEKAT KAKO BI SE SPRIJECILO GUBLJENJE URAÐENOG ZADATKA
4. NAZIVI FUNKCIJA, TE BROJ I TIP PARAMETARA MORAJU BITI IDENTICNI ONIMA KOJI SU KORIŠTENI U TESTNOM CODE-U, OSIM U SLUCAJU DA POSTOJI ADEKVATAN RAZLOG ZA NJIHOVU MODIFIKACIJU. OSTALE, POMOCNE FUNKCIJE MOŽETE IMENOVATI I DODAVATI PO ŽELJI.
5. IZUZETAK BACITE U FUNKCIJAMA U KOJIMA JE TO NAZNACENO.
****************************************************************************/

const char* crt = "\n-------------------------------------------\n";
const char* nedozvoljena_operacija = "Nedozvoljena operacija";
const char* not_set = "NOT_SET";
const int min_polgavlja = 3;
const int min_karaktera_po_poglavlju = 30;
mutex m;
char * AlocirajNizKaraktera(const char * sadrzaj) {
	if (sadrzaj == nullptr)
		return nullptr;
	int vel = strlen(sadrzaj) + 1;
	char * temp = new char[vel];
	strcpy_s(temp, vel, sadrzaj);
	return temp;
}

template<class T1, class T2>
class Kolekcija {
	T1 * _elementi1;
	T2 * _elementi2;
	int _trenutno;
public:
	Kolekcija() :_trenutno(0), _elementi1(nullptr), _elementi2(nullptr) { }
	Kolekcija(const Kolekcija &k) {
		_trenutno = k._trenutno;
		_elementi1 = new T1[_trenutno];
		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
	}
	Kolekcija &operator=(const Kolekcija &k) {
		if (this == &k) return *this;
		delete[]_elementi1; _elementi1 = nullptr;
		delete[]_elementi2; _elementi2 = nullptr;
		_trenutno = k._trenutno;
		_elementi1 = new T1[_trenutno];		_elementi2 = new T2[_trenutno];
		for (size_t i = 0; i < _trenutno; i++)
		{
			_elementi1[i] = k._elementi1[i];
			_elementi2[i] = k._elementi2[i];
		}
		return *this;
	}
	void AddElement(const T1 &el1,const T2 &el2) {
		T1* temp1 = new T1[_trenutno + 1];
		T2* temp2 = new T2[_trenutno + 1];

		for (size_t i = 0; i < _trenutno; i++)
		{
			temp1[i] = _elementi1[i];
			temp2[i] = _elementi2[i];
		}
		delete[] _elementi1;
		delete[] _elementi2;
		temp1[_trenutno] = el1;
		temp2[_trenutno] = el2;
		_elementi1 = temp1; temp1 = nullptr;
		_elementi2 = temp2; temp2 = nullptr;
		_trenutno++;
	}
	~Kolekcija() {
		delete[] _elementi1; _elementi1 = nullptr;
		delete[] _elementi2; _elementi1 = nullptr;
	}
	T1 * getElementi1Pok() { return _elementi1; }
	T2 * getElementi2Pok() { return _elementi2; }
	T1 & getElement1(int lokacija) { return _elementi1[lokacija]; }
	T2 & getElement2(int lokacija) { return _elementi2[lokacija]; }
	int getTrenutno() { return _trenutno; }

	friend ostream & operator<<(ostream & COUT, Kolekcija<T1, T2> & obj) {
		for (size_t i = 0; i < obj._trenutno; i++)
			COUT << obj.getElement1(i) << " " << obj.getElement2(i) << endl;
		return COUT;
	}
};
class Poglavlje {
	char * _naslov;
	char * _sadrzaj;
	bool _prihvaceno;
	int _ocjena;//da bi se poglavlje smatralo prihvacenim ocjena mora biti u opsegu od 6 - 10
public:
	Poglavlje(const char * naslov = nullptr, const char * sadrzaj = nullptr)
		:_ocjena(0), _prihvaceno(false) {
		_naslov = AlocirajNizKaraktera(naslov);
		_sadrzaj = AlocirajNizKaraktera(sadrzaj);
	}
	Poglavlje(const Poglavlje &p) {
		_naslov = AlocirajNizKaraktera(p._naslov);
		_sadrzaj = AlocirajNizKaraktera(p._sadrzaj);
		_ocjena = p._ocjena;
		_prihvaceno = p._prihvaceno;
	}
	Poglavlje &operator=(const Poglavlje &p) {
		if (this == &p) return *this;
		delete[]_naslov; _naslov = nullptr;
		delete[]_sadrzaj; _sadrzaj = nullptr;
		_naslov = AlocirajNizKaraktera(p._naslov);
		_sadrzaj = AlocirajNizKaraktera(p._sadrzaj);
		_ocjena = p._ocjena;
		_prihvaceno = p._prihvaceno;
		return *this;
	}
	bool operator==(const Poglavlje &p) {
		strcmp(p._naslov, _naslov) == 0;
	}
	Poglavlje() {
		delete[] _naslov; _naslov = nullptr;
		delete[] _sadrzaj; _sadrzaj = nullptr;
	}
	friend ostream & operator<<(ostream & COUT, Poglavlje & obj) {
		if (obj._naslov == nullptr || obj._sadrzaj == nullptr)
			return COUT;
		COUT << endl << obj._naslov << endl << obj._sadrzaj << endl;
		if (obj._prihvaceno)
			COUT << "Ocjena: " << obj._ocjena << endl;;
		return COUT;
	}
	char * GetNaslov() { return _naslov; }
	char * GetSadrzaj() { return _sadrzaj; }
	bool GetPrihvaceno() { return _prihvaceno; }
	int GetOcjena() { return _ocjena; }
	void DodajSadrzaj(string sadrzaj) {
		string stari = _sadrzaj;
		stari += sadrzaj;
		delete[]_sadrzaj;
		_sadrzaj = AlocirajNizKaraktera(stari.c_str());
	}
	void OcijeniPoglavlje(int ocjena) {
		if (ocjena > 5 && ocjena < 11)
			_prihvaceno = true;
		_ocjena = ocjena;
	}
};

class ZavrsniRad {
	char* _tema;
	vector<Poglavlje> _poglavljaRada;
	string _datumOdbrane;
	float _konacnaOcjena; //prosjek ocjena svih poglavlja u zavrsnom radu koja se izracunava u momentu zakazivanja odbrane
public:
	ZavrsniRad(const char * nazivTeme = nullptr) : _konacnaOcjena(0), _datumOdbrane(not_set) {
		_tema = AlocirajNizKaraktera(nazivTeme);
	}

	ZavrsniRad(const ZavrsniRad& org) : _poglavljaRada(org._poglavljaRada), _konacnaOcjena(org._konacnaOcjena), _datumOdbrane(org._datumOdbrane) {
		_tema = AlocirajNizKaraktera(org._tema);
	}
	ZavrsniRad& operator=(const ZavrsniRad& z) {
		if (this == &z) return *this;
		delete[]_tema; _tema = nullptr;
		_tema = AlocirajNizKaraktera(z._tema);
		_poglavljaRada = z._poglavljaRada;
		_datumOdbrane = z._datumOdbrane;
		_konacnaOcjena = z._konacnaOcjena;
		return *this;
	}
	bool operator==(const ZavrsniRad &z) {
		return strcmp(z._tema, _tema) == 0;
	}
	void SetKonacnaOcjena(float ocjena) { _konacnaOcjena = ocjena; }
	~ZavrsniRad() {
		delete[] _tema; _tema = nullptr;
	}
	char* GetNazivTeme()const { return _tema; }
	vector<Poglavlje>& GetPoglavlja() { return _poglavljaRada; };
	string GetDatumOdbrane()const { return _datumOdbrane; }
	float GetOcjena() { return _konacnaOcjena; }
	void SetDatumOdbrane(string datumOdbrane) { _datumOdbrane = datumOdbrane; }

	friend ostream& operator<<(ostream& COUT, ZavrsniRad& obj) {
		COUT << "Tema rada: " << obj._tema << endl;
		COUT << "Sadrzaj: " << endl;
		for (size_t i = 0; i < obj._poglavljaRada.size(); i++)
			COUT << obj._poglavljaRada[i] << endl;
		COUT << "Datum odbrane rada: " << obj._datumOdbrane << endl << " Ocjena: " << obj._konacnaOcjena << endl;
		return COUT;
	}
	void DodajPoglavlje(string naslov, string sadrzaj) {
		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i < _poglavljaRada.end(); i++)
		{
			if (i->GetNaslov() == naslov) {
				i->DodajSadrzaj(sadrzaj);
				return;
			}
		}
		_poglavljaRada.push_back(Poglavlje(naslov.c_str(), sadrzaj.c_str()));
	}
	void OcijeniPoglavlje(string naslov, int ocjena) {
		bool postojiPoglavlje = false;
		for (vector<Poglavlje>::iterator i = _poglavljaRada.begin(); i < _poglavljaRada.end(); i++)
		{
			if (i->GetNaslov() == naslov) {
				i->OcijeniPoglavlje(ocjena);
				postojiPoglavlje = true;
				return;
			}
		}
		if (!postojiPoglavlje) {
			//koristimo jer ima try catch u mainu.
			throw exception("Ovo poglavlje ne postoji. ");
		}
	}
};

class Osoba {
protected:
	string _imePrezime;
public:
	Osoba(string imePrezime) : _imePrezime(imePrezime) {}
	string GetImePrezime() { return _imePrezime; }
	virtual void Info() = 0;
};

class Nastavnik :public Osoba {
	//Parametar string predstavlja broj indeksa studenta koji prijavljuje zavrsni rad kod odredjenog nastavnika
	Kolekcija<string, ZavrsniRad> _teme;
public:
	Nastavnik(string imePrezime) :Osoba(imePrezime) {}
	Nastavnik(const Nastavnik &n) :Osoba(n) {}
	Kolekcija<string, ZavrsniRad>& GetTeme() { return _teme; };
	friend ostream &operator<<(ostream &c, Nastavnik &n) {
		c << "Ime i prezime: " << n._imePrezime << endl;
		c << "Teme: " << n._teme << endl;
		return c;
	}
	void Info() {
		cout << *this << endl;
	}
	bool DodajZavrsniRad(string brojIndexa, ZavrsniRad z) {
		/*funkcija DodajZavrsniRad ima zadatak da odredjenom nastavniku dodijeli mentorstvo na zavrsnom radu.
		zavrsni rad se dodaje studentu sa brojem indeksa proslijedjenim kao prvi parametar.
		sprijeciti dodavanje zavrsnih radova sa istom temom*/
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			if (_teme.getElement1(i) == brojIndexa || _teme.getElement2(i) == z) {
				return false;
			}
		}
		_teme.AddElement(brojIndexa, z);
		return true;
	}
	ZavrsniRad *ZakaziOdbranuRada(string brojIndexa, string datumOdbrane) {
		/*funkcija ZakaziOdbranuRada ima zadatak da studentu sa proslijedjenim brojem indeksa zakaze odbranu zavrsnog rada sto podrazumijeva definisanje
		datuma odbrane. odbrana rada se moze zakazati samo studentu koji je rad prethodno prijavio i pri tom su zadovoljeni sljedeci uslovi:
		1. zavrsni rad ima broj poglavlja veci od minimalnog
		2. svako poglavlje ima broj karaktera veci od minimalnog
		3. svako poglavlje je prihvaceno/odobreno
		ukoliko su zadovoljeni prethodni kriteriji, izracunava se konacna ocjena rada (prosjek ocjena svih poglavlja), postavlja datum odbrane rada i vraca pokazivac na rad kome je zakazan odbrana.
		u slucaju da student sa primljenim brojem indeksa nije prijavio zavrsni rad ili neki od postavljenih kriterija nije zadovoljen, funkcija vraca nullptr.
		*/
		ZavrsniRad *z = nullptr;
		for (size_t i = 0; i < _teme.getTrenutno(); i++)
		{
			//provjera da li postoji ovaj student.
			if (_teme.getElement1(i) == brojIndexa) {
				float prosjek = 0; int brojac = 0;
				for (vector<Poglavlje>::iterator j = _teme.getElement2(i).GetPoglavlja().begin(); j < _teme.getElement2(i).GetPoglavlja().end(); j++)
				{
					if (strlen(j->GetSadrzaj()) < min_karaktera_po_poglavlju)
						return nullptr;
					if (!j->GetPrihvaceno())
						return nullptr;
					prosjek += j->GetOcjena(); brojac++;
				}
				prosjek /= brojac;
				_teme.getElement2(i).SetDatumOdbrane(datumOdbrane);
				_teme.getElement2(i).SetKonacnaOcjena(prosjek);
				z = &_teme.getElement2(i);
			}
		}
		return z;
	}
};
string PosaljiPozivZaDodjeluNagrada(Nastavnik **n, int maxUcenika, int maxProsjek) {

	/*Funkcija PosaljiPozivZaDodjeluNagrada ima zadatak da svim studentima koji su uspjesno okoncali svoj zavrsni rad kod odredjenog nastavnika/mentora
	i tom prilikom ostvarili ocjenu vecu od proslijedjene, u zasebnom thread.u, posalje email poruku (mail adresa: brojIndeksa@edu.fit.ba) sa sadrzajem:
	"Postovani {brojIndeksa}, uzimajuci u obzir cinjenicu da ste kod mentora {imePrezimeMentora} uspjesno odbranili rad sa ocjenom {ocjena} cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine."	.
	funkcija treba da vrati sadrzaj svih poslatih email poruka, a ukoliko niti jedan od nastavnika ne posjeduje evidentirano mentorstvo na zavrsnom radu, funkcija vraca not_set*/

	//funkcija je string jer u mainu salje se preko cout<<
	bool ostvarenUspjeh = false;
	stringstream ss;
	for (size_t i = 0; i < maxUcenika; i++)
	{
		//otvaramo forpetlju sa svim zavrsnim radovima
		for (size_t j = 0; j < n[i]->GetTeme().getTrenutno(); j++)
		{
			if (n[i]->GetTeme().getElement2(j).GetOcjena() > maxProsjek) {
				ostvarenUspjeh = true;
				thread prvi([&] {
					m.lock();
					ss << "Postovani " << n[i]->GetTeme().getElement1(i) << ", uzimajuci u obzir cinjenicu da ste kod mentora " << n[i]->GetImePrezime() << " uspjesno odbranili rad sa ocjenom " << n[i]->GetTeme().getElement2(j).GetOcjena() << " cast nam je pozvati vas na dodjelu nagrada za najbolje studente koja ce se odrzatu u na FIT-u 03.07.2019. godine." << endl;
					m.unlock();
				});
				prvi.join();
			}
		}
	}
	if (ostvarenUspjeh)
		return ss.str();
	else
		return "not_set";
}
int main() {
	cout << crt << "UPLOAD RADA OBAVEZNO IZVRSITI U ODGOVARAJUCI FOLDER NA FTP SERVERU" << endl;
	cout << "U slucaju da je Upload folder prazan pritisnite tipku F5" << crt;

	const int max = 4;
	Nastavnik * nastavnici[max];

	nastavnici[0] = new Nastavnik("Denis Music");
	nastavnici[1] = new Nastavnik("Zanin Vejzovic");
	nastavnici[2] = new Nastavnik("Jasmin Azemovic");
	nastavnici[3] = new Nastavnik("Emina Junuz");
	//parametri: naziv zavrsnog rada
	ZavrsniRad multimedijalni("Multimedijalni informacijski sistem za visoko - obrazovnu ustanovu");
	ZavrsniRad podrsa_operaterima("Sistem za podršku rada kablovskog operatera");
	ZavrsniRad analiza_sigurnosti("Prakticna analiza sigurnosti bežicnih racunarskih mreža");
	ZavrsniRad kriptografija("Primjena teorije informacija u procesu generisanja kriptografskih kljuceva");

	/*u zavrsni rad dodaje novo poglavlje i njegov sadrzaj. ukoliko poglavlje vec postoji u zavrsnom radu, funkcija tom poglavlju treba dodati novi sadrzaj i pri tome zadrzi postojeci (izmedju postojeceg i novog sadrzaja se dodaje prazan prostor). u slucaju da poglavlje ne postoji, ono se dodaje zajedno sa sadrzaje*/
	//parametri: nazivPoglavlja, sadrzajPoglavlja
	multimedijalni.DodajPoglavlje("Uvod", "U ovom poglavlju ce biti rijeci");
	multimedijalni.DodajPoglavlje("Uvod", "o multimedijalnim sistemima koji se danas koriste");
	multimedijalni.DodajPoglavlje("Uvod", "u savremenom poslovanju");
	multimedijalni.DodajPoglavlje("Vrste multimedijalnih sistema", "Danas se moze govoriti o nekoliko vrsta multimedijalnih sistema, a neke od najznacajnijih su ...");
	multimedijalni.DodajPoglavlje("Teorija multimedije", "Sadrzaj koji bi trebao stajati na pocetku treceg poglavlja zavrsnog rada o multimediji studenta IB130011");
	multimedijalni.DodajPoglavlje("Zakljucak", "U ovom radu su predstavljeni osnovni koncepti i prakticna primjena...");

	//provjera
	//cout << multimedijalni << endl;
	try {
		/*funkcija OcijeniPoglavlje, na osnovu naziva poglavlja, dodjeljuje ocjenu poglavlju te ukoliko je ocjena pozitivna (6 - 10) onda poglavlje oznacava prihvacenim. U slucaju da ocjena nije validna ili poglavlje ne postoji, funkcija baca izuzetak sa odgovarajucom porukom*/
		//parametri:nazivPoglavlja, ocjena

		multimedijalni.OcijeniPoglavlje("Uvod", 8);
		multimedijalni.OcijeniPoglavlje("Vrste multimedijalnih sistema", 8);
		multimedijalni.OcijeniPoglavlje("Teorija multimedije", 9);
		multimedijalni.OcijeniPoglavlje("Zakljucak", 7);
		multimedijalni.OcijeniPoglavlje("Naziv poglavlja ne postoji", 8);
	}
	catch (exception & err) {
		cout << "Greska -> " << err.what() << endl;
	}


	//parametri: brojIndeksa, zavrsniRad
	if (nastavnici[0]->DodajZavrsniRad("IB130011", multimedijalni))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[0]->DodajZavrsniRad("IB120051", podrsa_operaterima))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120056", podrsa_operaterima))//dupliranje rada
		cout << "Zavrsni rad nije dodat!" << endl;
	if (!nastavnici[0]->DodajZavrsniRad("IB120051", kriptografija)) //studentu vec dodijeljen rad
		cout << "Zavrsni rad nije dodat!" << endl;
	if (nastavnici[1]->DodajZavrsniRad("IB140102", analiza_sigurnosti))
		cout << "Zavrsni rad uspjesno dodat!" << endl;
	if (nastavnici[2]->DodajZavrsniRad("IB140002", kriptografija))
		cout << "Zavrsni rad uspjesno dodat!" << endl;



	//parametri: brojIndeksa, datumOdbrane
	ZavrsniRad * zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130011", "25.09.2018");
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	zr1 = nastavnici[0]->ZakaziOdbranuRada("IB130111", "25.09.2018");//student sa brojem indeksa IB130111 jos uvijek nije prijavio rad
	if (zr1 != nullptr)
		cout << *zr1 << endl;

	//ispisuje sve podatke o nastavniku i njegovim mentorstvima
	nastavnici[0]->Info();

	cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 9.5) << endl;
	//provjera sa manjim nekim prosjekom
	//cout << "Studenti za dodjelu nagrada: " << PosaljiPozivZaDodjeluNagrada(nastavnici, max, 7) << endl;
	for (int i = 0; i < max; i++) {
		delete nastavnici[i];
		nastavnici[i] = nullptr;
	}
	system("pause");
	return 0;
}

