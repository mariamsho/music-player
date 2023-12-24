#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>
#include <map>

using namespace std;


class Song {
private:
	string song;
	string date;
	Song* next;
	Song* prev;
	int day, month, year;
	int playscount = 0;


public:

	void dateConvert(string date) {				//converts date from string to int day-month-year

		day = date[0] * 10 + date[1];
		month = date[3] * 10 + date[4];
		year = date[6] * 1000 + date[7] * 100 + date[8] * 10 + date[9];

	}

	Song(string  name, string d) {
		song = name;
		date = d;
		dateConvert(date);
		next = nullptr;
	}

	

	void setSongName(string name) { song = name; }
	string getSongName() { return song; }

	void setDate(string d) { date = d; }
	string getDate() { return date; }

	void setNext(Song* n) { next = n;}
	Song* getNext() { return next; }
	void setPrev(Song* p) { prev = p; }
	Song* getPrev() { return prev; }

	int getDay() { return day; }
	int getMonth() { return month; }
	int getYear() { return year; }

	int getPlays() { return playscount; }
	void addPlays() { playscount++; }
	
	~Song() {}


};

class Playlist {
private:
	Song* first = nullptr;
	Song* last;

public:
	Playlist() : first(nullptr), last(nullptr) {}

	void addSong(Song* x){ 
		if (first == nullptr) {
			first = x;
			last = x;
		}
		else {
			last->setNext(x);
			last = x;
			last->setNext(nullptr);
		}

	}

	Song* getFirst() { return first; }

	void remove(Song* song){
			Song* current = first;
			while (current->getNext() != nullptr) {
				if (current->getNext()->getSongName() == song->getSongName()) {
					current->setNext(current->getNext()->getNext());
					return;
				}
				current = current->getNext();

			}

		
	}


	void printPlaylist(){
		Song* current = first;
		while (current != nullptr) {
			cout << current->getSongName() << " ";
			current = current->getNext();
		}
		cout << endl;
	
	}

	bool compareDate(Song* s1, Song* s2) {			//if s1 > s2 return true

		if (s1->getYear() > s2->getYear()) {
			return true;
		}
		else if (s1->getYear() == s2->getYear()) {
			if (s1->getMonth() > s2->getMonth()) {
				return true;
			}
			else if (s1->getMonth() == s2->getMonth()) {
				if (s1->getDay() > s2->getDay()) {
					return true;
				}
				else {
					return false;
				}
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}


	} 

	void mergel(Song*& head, Song* l, Song* m, Song* r);
	void mergeSort(Song*& head, int l, int r);
	void mergePlaylists(vector<Playlist>& playlists, Playlist& mergedPlaylist)	;
	void display();
	

	

};

class MostPlayedSongs;

class RecentlyPlayedSongsList {

private:
	Song* first;
	Song* last;
	Song* current;
	unordered_map<string, Song*> songMap;


public:
	RecentlyPlayedSongsList() { first = nullptr; last = nullptr; }


	void remove(Song* s) {
		Song* curr = first;
		while (curr->getNext() != nullptr) {
			if (curr->getSongName() == s->getSongName()) {
				curr->getPrev()->setNext(curr->getNext());
				curr->getNext()->setPrev(curr->getPrev());
			}
			curr = curr->getNext();

		}
	}

	void addSong(Song* x) {
		if (first == nullptr) {
			first = x;
			last = x;
		}
		else {
			last->setNext(x);
			x->setPrev(last);
			last = x;
			last->setNext(nullptr);
		}
		songMap[x->getSongName()] = x;
	}
	

	void playSong(Song* s) {
		cout << "playing:" << s->getSongName() << endl;
		if (songMap.find(s->getSongName()) != songMap.end()) {//map checks if song is played before
			remove(s);						//if yes it is removed from list
			addSong(s);						//then added to the back of the list
			return;
		}
		addSong(s);					//if no it is only added
		s->addPlays();				//increment play count
		current = s;
	}

	void playNext() {
		current = current->getNext();
		if (current = nullptr) {
			cout << "No more songs";
			return;
		}
		playSong(current);
	}

	void playPrev() {
		current = current->getPrev();
		if(current = first) {
			cout << "Top of list!";
			return;
		}
		playSong(current);
	}


	void printPlaylist() {
		Song* current = first;
		while (current != nullptr) {
			cout << current->getSongName() << " ";
			current = current->getNext();
		}
		cout << endl;

	}

};

class MostPlayedSongs {
private:
	Song* first;
	Song* last;
	map<string, Song*> mostPlayedmap;

public:
	MostPlayedSongs() : first(0), last(0){}

	void addSong(Song* x) {

		insertSorted(x);
		if (mostPlayedmap.find(x->getSongName()) != mostPlayedmap.end()) {
			remove(x);
		}
		else {
			mostPlayedmap[x->getSongName()] = x;

		}
	}

	void remove(Song* s) {
		Song* curr = first;
		while (curr->getNext() != nullptr) {
			if (curr->getSongName() == s->getSongName()) {
				curr->getPrev()->setNext(curr->getNext());
				curr->getNext()->setPrev(curr->getPrev());
			}
			curr = curr->getNext();

		}
	}
	

	void insertSorted(Song* s) {
		if (first == nullptr || s->getPlays() >= first->getPlays()) {
			// If the list is empty or the new song has more plays than the first insert at the beginning
			s->setNext(first);
			if (first != nullptr) {
				first->setPrev(s);
			}
			first = s;
		}
		else {
			Song* current = first;

			while (current->getNext() != nullptr && s->getPlays() < current->getNext()->getPlays()) {
				current = current->getNext();
			}

			s->setNext(current->getNext());
			s->setPrev(current);
			if (current->getNext() != nullptr) {
				current->getNext()->setPrev(s);
			}
			current->setNext(s);
		}
	}


	void printPlaylist() {
		Song* current = first;
		while (current != nullptr) {
			cout << current->getSongName() << "  no of plays:" << current->getPlays();
			current = current->getNext();
		}
		cout << endl;

	}



};
//
int main() {

	Playlist playlist1;
	playlist1.addSong(new Song("song1", "01-03-2023"));
	playlist1.addSong(new Song("song2", "01-01-1943"));
	playlist1.addSong(new Song("song3", "01-02-2017"));

	Playlist playlist2;
	playlist2.addSong(new Song("song4", "01-05-2023"));
	playlist2.addSong(new Song("song5", "01-04-1999"));

	Playlist playlist3;
	playlist3.addSong(new Song("song6", "01-08-2023"));
	playlist3.addSong(new Song("song7", "01-07-2023"));
	playlist3.addSong(new Song("song8", "01-01-2023"));


	vector<Playlist> v;
	v.push_back(playlist1); v.push_back(playlist2); v.push_back(playlist3);



	Playlist mainPlaylist;
	mainPlaylist.mergePlaylists(v, mainPlaylist);

	mainPlaylist.display();
	//--------------------------------------------------------

	//string song1 = "song1";
	//string date = "11/12/1943";
	//Song* song = new Song(song1, date);

	//string date2 = "14/12/1943";
	//string song2 = "song2";
	//Song* songp = new Song(song2, date2);

	//string date3 = "11/12/1960";
	//string song3 = "song3";
	//Song* songz = new Song(song3, date3);


	//	RecentlyPlayedSongsList Recents;
	//	Recents.playSong(song);
	//	Recents.playSong(songp);
	//	Recents.playSong(songz);
	//	Recents.playSong(songp);
	//	Recents.playPrev();
	//	Recents.playNext();

	//	Recents.printPlaylist();

	////--------------------------------------------------------


	//	MostPlayedSongs mostplays;

	//	mostplays.addSong(songp);
	//	mostplays.addSong(song);
	//	mostplays.addSong(songz);

	//	mostplays.printPlaylist();









	//if (list.compareDate(song, songp)) { // if song p > songz print yes
	//	cout << "yes";
	//}
	//else {
	//	cout << "no";
	//}





}