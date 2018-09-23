#include <iostream>
#include <vector>
#include <stdio.h>
#include <fstream>

using namespace std;


struct Book
{
    string author;
    string title;
    string genre;

    Book(string Author, string Title, string Genre)
    {
        author = Author;
        title = Title;
        genre = Genre;
    }

    Book()
    {

    }

};

struct BookInventory
{
    Book * book;
    int numberOfBooks = 0;
    int ID;

    BookInventory(Book * bok, int number, int id)
    {
        book = bok;
        numberOfBooks = number;
        ID = id;
    }
    BookInventory()
    {

    }
};

class Library
{
    vector <BookInventory*> books;
    static int nextId;

public:

    BookInventory *searchForBook(string title, string author, string genre)
    {
        for (auto const &value: books)
        {
            if(value->book->title == title && value->book->author == author && value->book->genre == genre)
            {
                return value;
            }
        }

        return NULL;
    }
    BookInventory *searchForBook(int id)
    {
        for (auto const &value: books)
        {
            if(value->ID == id)
                return value;
        }
        return NULL;
    }
    void addBook(string author, string title, string genre)
    {
        BookInventory * temp = new BookInventory;
        Book * tBook = new Book;
        tBook->author = author;
        tBook->genre = genre;
        tBook->title = title;
        temp ->book = tBook;
        for (auto const &value: books)
            if(searchForBook(title,author,genre)!=NULL)
            {
                value->numberOfBooks++;
                return;
            }

            temp->ID = nextId;
            nextId++;
            temp->numberOfBooks++;
        books.push_back(temp);
    }
    void listBooks()
    {
        for (auto const &value: books)
            printf("Book: %s written by %s of genre %s has %d copies and has %d id number\n", value->book->title.c_str(),
                   value->book->author.c_str(), value->book->genre.c_str(), value->numberOfBooks, value->ID);
    }
    void saveToFile()
    {
        ofstream outputFile;
        outputFile.open("books.txt");
        for (auto const &value: books)
        {
            outputFile << value->book->title << " " << value->book->author << " "<< value->book->genre << " " << value->ID << " "<< value->numberOfBooks << endl;
        }
        outputFile.close();
    }
    void readFromFile()
    {
        ifstream saveFile;
        saveFile.open("books.txt");
        if(saveFile)
        {
            string author;
            string title;
            string genre;
            int id;
            int quantity;
            while (saveFile >> title >> author >> genre >> id >> quantity)
            {
                books.push_back(new BookInventory(new Book(author, title, genre), quantity, id));
            }
        }
        else
            return;
    }
};

int Library::nextId = 0;

int main()
{

    Library testLib;
    testLib.readFromFile();
    testLib.listBooks();
    testLib.addBook("GeorgeRRMartin", "GameOfThrones", "Fantasy");
    testLib.saveToFile();

    return 0;
}