#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "ppm.h"
#include "pgm.h"
#include "grayPixel.h"
#include "colorPixel.h"
#include<sstream>

using namespace std;

//http://people.uncw.edu/tompkinsj/112/texnh/assignments/imageFormat.html

class Rotator {
   static Rotator *instance;
    std::string originalFile;
    std::string rotatedFile;
    std::string rotationDirection;
    int rotationAngle;
 
    Rotator(){}

    public:
    static Rotator *getInstance() {
        if (!instance)
            instance = new Rotator();
        return instance;
    }
    string getOriginalFile() { return this -> originalFile; }
    void setOriginalFile(string originalFile) {this->originalFile = originalFile; }

    string getRotatedFile() { return this -> rotatedFile; }
    void setRotatedFile(string rotatedFile) {this->rotatedFile = rotatedFile; }

    string getRotationDirection() { return this -> rotationDirection; }
    void setRotationDirection(string rotationDirection) {this->rotationDirection = rotationDirection; }

    int getRotationAngle() { return this -> rotationAngle; }
    void setRotationAngle(int rotationAngle_) {this->rotationAngle = rotationAngle_; }

    private:
    PGM readPGMFileToVector(string filename) {
        ifstream inp;
        inp.open(filename, ios::in | ios::binary);

        vector<GrayPixel> grayPixels;
        int width, height, max_val;

        // vector<char> magicNumbers;
        // while (myfile >> magic)
        //     magicNumbers.push_back(magic);
        // myfile.close();
        std::string line;
        std::getline(inp, line);
        string magicNumber= line;

        std::getline(inp, line);
        while (line[0] == '#') {
            std::getline(inp, line);
        }
        std::stringstream dimensions(line);
        try {
            dimensions >> width;
            dimensions >> height;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
        }

        std::getline(inp, line);
        std::stringstream max_col_val(line);
        try {
            max_col_val >> max_val;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
        }

        int size = width*height;
        if(magicNumber=="P2"||magicNumber=="P3"){
            for(int i =0;i<height*width;i++) {
                getline(inp, line);
                GrayPixel temp(stoi(line));
                grayPixels.push_back(temp);
            }
        }
        else{
            vector<unsigned char> g;
            g.reserve(size);
            char aux;
            for(int i =0;i<height*width;i++){
                inp.read(&aux, 1);
                GrayPixel temp((unsigned char) aux);
                grayPixels.push_back(temp);
            }
        }
        PGM pgm(magicNumber, height, width, max_val, grayPixels);
        return pgm;
    }

    PPM readPPMFileToVector(string filename) {
        
        ifstream inp;
        inp.open(filename, ios::in | ios::binary);

        vector<ColorPixel> colorPixels;
        int width, height, max_val;

        // vector<char> magicNumbers;
        // while (myfile >> magic)
        //     magicNumbers.push_back(magic);
        // myfile.close();
        std::string line;
        std::getline(inp, line);
        string magicNumber= line;

        std::getline(inp, line);
        while (line[0] == '#') {
            std::getline(inp, line);
        }
        std::stringstream dimensions(line);
        try {
            dimensions >> width;
            dimensions >> height;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
        }

        std::getline(inp, line);
        std::stringstream max_col_val(line);
        try {
            max_col_val >> max_val;
        } catch (std::exception &e) {
            std::cout << "Header file format error. " << e.what() << std::endl;
        }

        int size = width*height;
        if(magicNumber=="P2"||magicNumber=="P3"){
            for(int i =0;i<height*width;i++) {
                getline(inp, line);
                int red =stoi(line);
                getline(inp, line);
                int green = stoi(line);
                getline(inp, line);
                int blue = stoi(line);
                ColorPixel temp(red, green, blue);
                colorPixels.push_back(temp);
            }
        }
        else{
            vector<unsigned char> g;
            g.reserve(size);
            char aux;
            for(int i =0;i<height*width;i++){
                inp.read(&aux, 1);
                int red = (unsigned char) aux;
                inp.read(&aux, 1);
                int green = (unsigned char) aux;
                inp.read(&aux, 1);
                int blue = (unsigned char) aux;
                ColorPixel temp(red, green, blue);
                colorPixels.push_back(temp);
            }
        }
        PPM ppm(magicNumber, height, width, max_val, colorPixels);
        return ppm;
    }

    vector<string> splitString(string my_str, char c) {
        vector<string> result;
        stringstream s_stream(my_str); //create string stream from the string
        while(s_stream.good()) {
            string substr;
            getline(s_stream, substr, c); //get first string delimited by comma
            result.push_back(substr);
        }
        return result;
    }

    void rotateFile(string rotatedFile, PGM pgm, int rotationAngle) {
        ofstream  outfile(rotatedFile, std::ios::out | std::ios::binary);
        outfile<<pgm.getMagicNumber()<<endl;
        outfile<<"#Comments"<<endl;
        int width = pgm.getWidth();
        int height = pgm.getHeight();
        vector<GrayPixel> grayPixels = pgm.getGrayPixels();
        vector<GrayPixel> outputPixels;

        while(rotationAngle>0){
            int w=0,h=0,idx=0;
            for(w =0;w<width;w++){
                for(h=0;h<height;h++){
                    idx=(height-1-h)*width+w;
                    GrayPixel g(grayPixels[idx].getGrayPixel());
                    outputPixels.push_back(g);
                }
            }
            swap(width, height);
            rotationAngle-=90;
            if(rotationAngle>0){
                grayPixels = outputPixels;
                outputPixels.clear();
            }
        }

        outfile<<width<<" "<<height<<endl;
        outfile<<pgm.getMaxValue()<<endl;
        cout<<outputPixels.size()<<endl;

        if(pgm.getMagicNumber()=="P2"||pgm.getMagicNumber()=="P3"){
            for(int idx =0;idx<pgm.getWidth()*pgm.getHeight();idx++)
                outfile<<outputPixels[idx].getGrayPixel()<<endl;
        }
        else{
            char aux;
            for(int idx =0;idx<pgm.getWidth()*pgm.getHeight();idx++){
                aux = (char) outputPixels[idx].getGrayPixel();
                outfile.write(&aux, 1);
            }
        }

        outfile.close();
    }

    void rotateFile(string rotatedFile, PPM ppm, int rotationAngle) {
        ofstream  outfile(rotatedFile, std::ios::out | std::ios::binary);
        outfile<<ppm.getMagicNumber()<<endl;
        outfile<<"#Comments"<<endl;
        int width = ppm.getWidth();
        int height = ppm.getHeight();
        vector<ColorPixel> colorPixels = ppm.getColorPixels();
        vector<ColorPixel> outputPixels;

        while(rotationAngle>0){
            cout<<rotationAngle<<endl;
            int w=0,h=0,idx=0;
            for(w =0;w<width;w++){
                for(h=0;h<height;h++){
                    idx=(height-1-h)*width+w;
                    ColorPixel c(colorPixels[idx].getRed(), colorPixels[idx].getGreen(), colorPixels[idx].getBlue());
                    outputPixels.push_back(c);
                }
            }
            swap(width, height);
            rotationAngle-=90;
            if(rotationAngle>0){
                colorPixels = outputPixels;
                outputPixels.clear();
            }
        }
        outfile<<width<<" "<<height<<endl;
        outfile<<ppm.getMaxValue()<<endl;
        cout<<outputPixels.size()<<endl;

        int i=0,j=0,idx=0;

        if(ppm.getMagicNumber()=="P2"||ppm.getMagicNumber()=="P3"){
            for(int idx =0;idx<ppm.getWidth()*ppm.getHeight();idx++){
                outfile<<outputPixels[idx].getRed()<<endl;
                outfile<<outputPixels[idx].getGreen()<<endl;
                outfile<<outputPixels[idx].getBlue()<<endl;
            }
        }
        else{
            char aux;
            for(int idx =0;idx<ppm.getWidth()*ppm.getHeight();idx++){
                aux = (char) outputPixels[idx].getRed();
                outfile.write(&aux, 1);
                aux = (char) outputPixels[idx].getGreen();
                outfile.write(&aux, 1);
                aux = (char) outputPixels[idx].getBlue();
                outfile.write(&aux, 1);                
            }
        }
        outfile.close();
    }

    public:
    void rotator(){
        vector<string> file = splitString(originalFile, '.');
        string extension=file[1];
        if(rotationDirection=="-l"){
            cout<<"Rotation start"<<endl;
            if(rotationAngle==90) rotationAngle=270;
            else if (rotationAngle==270) rotationAngle=90;
        }
        if(extension=="ppm") {        
            PPM ppm=readPPMFileToVector(originalFile);
            rotateFile(rotatedFile, ppm, rotationAngle);
        }
        else if(extension=="pgm"){
            PGM pgm = readPGMFileToVector(originalFile);
            cout<<"magicNumber: "<<pgm.getMagicNumber()<<" width: "<<pgm.getWidth()<<" height: "<<pgm.getHeight()<<" maxSize: "<<1<<endl;
            rotateFile(rotatedFile, pgm, rotationAngle);
        }
        else{
            cout<<"Format not supported"<<endl;
        }
    }
};
    Rotator *Rotator::instance = 0;

int main(int argc,  char **argv)
{
    //Store headers in ppm/pgm file
    //Check if binary or ascii and parse them
    //Store all pixels
    //Rotate pixels and write in new file
    
    string originalFile(argv[1]);
    string rotatedFile(argv[2]);
    string rotationDirection(argv[3]);
    string rotationAngle(argv[4]);

    Rotator *s = s->getInstance();
    s->setOriginalFile(originalFile);
    s->setRotatedFile(rotatedFile);
    s->setRotationAngle(stoi(rotationAngle));
    s->setRotationDirection(rotationDirection);

    s->rotator();
    return 0;

}