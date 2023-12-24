#include "Song.cpp"
#include<iostream>
#include<string>
#include<vector>
#include <unordered_map>
#include <map>

/////////merge sort////////////////////


void Playlist:: mergel(Song*& head, Song* l, Song* m, Song* r) {
    Song* current = nullptr;
    Song* left = l;
    Song* right = m;

    while (left != nullptr && right != r->getNext()) {
        if (compareDate(left, right)) {
            if (current == nullptr) {
                head = left;
            }
            else {
                current->setNext(left);
            }
            current = left;
            left = left->getNext();
        }
        else {
            if (current == nullptr) {
                head = right;
            }
            else {
                current->setNext(right);
            }
            current = right;
            right = right->getNext();
        }
    }

    // Copy the remaining elements of left[], if there are any
    while (left != nullptr) {
        current->setNext(left);
        current = left;
        left = left->getNext();
    }

    // Copy the remaining elements of right[], if there are any
    while (right != r->getNext()) {
        current->setNext(right);
        current = right;
        right = right->getNext();
    }
}

void Playlist::mergeSort(Song*& head, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;

        // Find middle node
        Song* current = head;
        for (int i = 0; i < m; ++i) {
            current = current->getNext();
        }
        Song* middle = current->getNext();

        current->setNext(nullptr);

        // Recursively sort both halves
        mergeSort(head, l, m);
        mergeSort(middle, 0, r - m);

        // Merge the sorted halves
        mergel(head, head, middle, current);
    }
}


void Playlist::mergePlaylists(std::vector<Playlist>& playlists, Playlist& mergedPlaylist) {

    for ( int i = 0; i < playlists.size(); i++) {

        Song* currentSong = playlists[i].getFirst();

        while (currentSong != nullptr) {
            mergedPlaylist.addSong(new Song(currentSong->getSongName(), currentSong->getDate()));
            currentSong = currentSong->getNext();
        }
    }

    int count = 0;
    Song* currentsize = this->getFirst();
    while (currentsize != nullptr) {
        count++;
        currentsize = currentsize->getNext();
    }

    Song* mergedHead = mergedPlaylist.getFirst();
    mergedPlaylist.mergeSort(mergedHead, 0, count);
}



void Playlist::display() {
    Song* current = first;
    while (current != nullptr) {
        std::cout << current->getDate() << " ";
        current = current->getNext();
    }
    cout << endl;
}





