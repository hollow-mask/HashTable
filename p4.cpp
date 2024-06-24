#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cctype>
#include <sstream>
using namespace std;

// Store the return of this function as an unsigned long!
unsigned long djb2(string str) {
   const char *ptr = str.c_str();
   unsigned long hash = 5381;
   int c;
   while ((c = *ptr++)) {
      hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
   }
   return hash;
}


string readwords(string l){
    int size = l.size();
    string justwords;
    for(int i =0; i < size;i++){
        if(!isalpha(l[i])){
            justwords += " ";
        }
        else justwords += l[i];
    }
    return justwords;
}

class Bucket{
    private:
        string key;
        bool isempty;
        int coll;
        vector<int> linenumb;
    public:

        Bucket(){
            isempty = true;
            coll = 0;
        }


        string getkey(){
            return key;
        }

        void setkey(string n){
            key = n;
            isempty = false;
        }

        bool empty(){
            return isempty;
        }

        void setempty(bool yon){
            isempty = yon;
        }

        void addline(int l){
            linenumb.push_back(l);
        }

        vector<int> getlines(){
            return linenumb;
        }

        int getcollisions(){
            return coll;
        }

        void addcoll(int c){
            coll= c;
        }
        // ostream& operator<<(ostream& os, const Bucket& obj){

        //     os << obj.key;
        //     return os;
        // }


};

ostream& operator<<(ostream& os, Bucket& obj){
    os << obj.getkey();
    return os;
}

class HashTable {
    private:
           
        int size;

    public:
        vector<Bucket> words;

    HashTable(int s, Bucket b){
        size = s;
        for(int i =0;i<size;i++){
            words.push_back(b);
        }
    }

    

    int getsize(){
        return size;
    }

    


    void insert(string word, string coll, int l, int dubhash){
        //cout<<"he@y"<<endl;
        unsigned long loc = djb2(word) % size;
        int c = 0;
        int cq =0;
        int cdh = 0;
        //cout<<"hey$"<<endl;
        //unsigned long loc2 = dubhash - (djb2(word) % dubhash);
        //cout<<loc<<endl;
        //cout<<"hey"<<endl;if(words.at(loc).getkey() ==word){
           
           

         if(words.at(loc).empty()==true){
                //cout<<"***"<<endl;
                //if(coll == "lp"){
                    //cout<<"hey"<<endl;
                    words.at(loc).setkey(word);
                    words.at(loc).setempty(false);
                    words.at(loc).addline(l);
                    //cout<<"Inserting word at line"<<l<<" "<<word<<loc<<endl;
                    //cout<<words.at(loc)<<endl;/////
                    
                //}
        }
        else if(words.at(loc).getkey() ==word){
            words.at(loc).addline(l);
        }
        else{
            if(coll == "lp"){
                
                unsigned long newloc;

                if(words.at(loc).getkey() !=word){
                    c++;
                }
                   
                for(int i=1; i< size;i++){
                     
                    newloc = (loc + i) % size;
                   
                    //cout<<words.at(newloc).getcollisions()<<endl;
                    
                    if(words.at(newloc).empty()==true){
                        words.at(newloc).setkey(word);
                        words.at(newloc).addline(l);
                        //cout<<"Inserting word at line"<<l<<" "<<word<<loc<<endl;
                        words.at(newloc).setempty(false);
                        //cout<<words.at(newloc)<<endl;
                        words.at(newloc).addcoll(c);
                        //cout<<c<<" is new collision number for "<< word <<endl;
                        // cout<<words.at(newloc).getcollisions()<<endl;
                        break;
                    }
                    else if(words.at(newloc).getkey() != word){
                        c++;
                    }
                    else if(words.at(newloc).getkey() == word){
                            
                            words.at(newloc).addline(l);
                            //cout<<"Inserting word at line"<<l<<" "<<word<<loc<<endl;
                            break;

                    }
                    
                    
                }
                
            }
            else if(coll == "qp"){
                
                unsigned long newloc;

                if(words.at(loc).getkey() !=word){
                    //cout<<"OOPs "<<word<<" u collided with "<<words.at(loc).getkey()<<endl;
                    cq++;
                }
                
                 for(int i=1; i< size;i++){
                    newloc = (loc + (i * i)) % size;

                    

                    if(words.at(newloc).empty()==true){
                        words.at(newloc).setkey(word);
                        words.at(newloc).addline(l);
                        words.at(newloc).setempty(false);
                        words.at(newloc).addcoll(cq);
                        //cout<<words.at(newloc).getcollisions()<<endl;
                        //cout<<words.at(newloc)<<endl;
                        break;
                    }
                    else if(words.at(newloc).getkey() != word){
                        //cout<<"OOPs "<<word<<" u collided with "<<words.at(newloc).getkey()<<endl;
                        cq++;
                    }
                    else if(words.at(newloc).getkey() == word){
                           
                            words.at(newloc).addline(l);
                            break;
                            //cout<<"Inserting word at line"<<l<<" "<<word<<loc<<endl;

                    }
                    // else{
                    //     cq++;
                    // }
                    
                 }
                 

            }
            else if(coll == "dh"){
                
                unsigned long loc2 = dubhash - (djb2(word) % dubhash);

                
                unsigned long newloc;

                
                if(words.at(loc).getkey() !=word){
                    cdh++;
                }
                
                for(int i=1; i< size;i++){
                    
                    newloc = (loc + (i * loc2)) % size;
                    
                    if(words.at(newloc).empty()==true){
                        words.at(newloc).setkey(word);
                        words.at(newloc).addline(l);
                        words.at(newloc).setempty(false);
                        words.at(newloc).addcoll(cdh);
                        //cout<<words.at(newloc)<<endl;
                        break;
                    }
                    else if(words.at(newloc).getkey() != word){
                        cdh++;
                    }
                    else if(words.at(newloc).getkey() == word){
                            
                            words.at(newloc).addline(l);
                            //cout<<"Inserting word at line"<<l<<" "<<word<<loc<<endl;
                        break;
                    }
                   
                }
                

            }
        }
            //cout<<"$$$"<<endl;
        //cout<<word<<endl;
        
    }

    void find(string word, string coll, int a){
         unsigned long loc = djb2(word) % size;
         bool inhash = false;
         bool nonexfound = false;
        if(words.at(loc).empty()==true){
            cout<<word<<" appears on lines []"<<endl;
             cout<<"The search had 0 collisions"<<endl;
        }

        if(words.at(loc).getkey() == word){
            
            vector<int> ls = words.at(loc).getlines();
            int s = ls.size();
            cout<<word<<" appears on lines [";
            for(int i =0; i < s; i++){
               
                    
                        if(i == s - 1){
                            cout<<ls.at(i)<<"]"<<endl;
                        }
                        else{
                            cout<<ls.at(i)<<",";
                    
                       }   
                    
            }
            cout<<"The search had 0 collisions"<<endl;
            cout<<endl;
        }
        else{
            if(coll == "lp"){
    
                unsigned long newloc;
                int sc = 1;  
                
                    //sc++;
                
                for(int i=1; i< size;i++){
                 
                    newloc = (loc + i) % size;
                    if(words.at(newloc).getkey() == word){
                        
                        inhash = true;
                        vector<int> ls = words.at(newloc).getlines();
                        int s = ls.size();
                        //cout<<s<<endl;
                        cout<<word<<" appears on lines [";
                        for(int i =0; i < s; i++){
                                
                            if(i == s - 1){
                                cout<<ls.at(i)<<"]"<<endl;
                            }
                            else{
                                cout<<ls.at(i)<<",";
                    
                            }   
                        }
                        if(inhash == true){
                            cout<<"The search had "<< sc <<" collisions"<<endl;
                            cout<<endl;
                        }
                        break;   
                    }
                    else if(words.at(newloc).empty() == true){
                        cout<<word<<" appears on lines []"<<endl;
                        cout<<"The search had "<<sc<<" collisions"<<endl;
                        nonexfound = true;
                        break;
                    }
                    else{
                        sc++;
                    }
                }

                if(inhash == false && nonexfound == false){
                    cout<<word<<" appears on lines []"<<endl;
                    cout<<"The search had "<<sc<<" collisions"<<endl;
                }
            }
            else if(coll == "qp"){
                unsigned long newloc;
                int c = 1;
                
                //c++;  
                for(int i=1; i< size;i++){
                    // cout<<word<<" collisison number "<<c<<endl;
                    // cout<<"**"<<words.at(newloc).getkey()<<endl;
                    newloc = (loc + (i * i)) % size;
                    
                    if(words.at(newloc).getkey() == word){
                        
                        inhash = true;
                        vector<int> ls = words.at(newloc).getlines();
                        int s = ls.size();
                        //cout<<s<<endl;
                        cout<<word<<" appears on lines [";
                        for(int i =0; i < s; i++){
                                
                            if(i == s - 1){
                                cout<<ls.at(i)<<"]"<<endl;
                            }
                            else{
                                cout<<ls.at(i)<<",";
                    
                            }   
                        }
                        if(inhash == true){
                            cout<<"The search had "<< c <<" collisions"<<endl;
                            cout<<endl;
                        }
                        break;   
                    }
                    else if(words.at(newloc).empty() == true){
                        cout<<word<<" appears on lines []"<<endl;
                        cout<<"The search had "<<c<<" collisions"<<endl;
                        
                        nonexfound = true;
                        break;
                    }
                    else{
                        c++;
                    }
                }

                if(inhash == false && nonexfound == false ){
                    cout<<word<<" appears on lines []"<<endl;
                    cout<<"The search had "<< c <<" collisions"<<endl;
                }
                

            }
            else if(coll == "dh"){
                unsigned long loc2 = a - (djb2(word) % a);
                unsigned long newloc;
                int c =0;
                c++;
                 for(int i=1; i< size;i++){
                    newloc = (loc + (i * loc2)) % size;
                    
                    if(words.at(newloc).getkey() == word){
                        
                        inhash = true;
                        vector<int> ls = words.at(newloc).getlines();
                        int s = ls.size();
                        //cout<<s<<endl;
                        cout<<word<<" appears on lines [";
                        for(int i =0; i < s; i++){
                                
                            if(i == s - 1){
                                cout<<ls.at(i)<<"]"<<endl;
                            }
                            else{
                                cout<<ls.at(i)<<",";
                    
                            }   
                        }
                        if(inhash == true){
                            cout<<"The search had "<< c <<" collisions"<<endl;
                            cout<<endl;
                        }
                        break;   
                    }
                    else if(words.at(newloc).empty() == true){
                        cout<<word<<" appears on lines []"<<endl;
                        cout<<"The search had "<<c<<" collisions"<<endl;
                        nonexfound = true;
                        break;
                    }
                    else{
                        c++;
                    }
                }

                if(inhash == false && nonexfound == false){
                    cout<<word<<" appears on lines []"<<endl;
                    cout<<"The search had "<< c <<" collisions"<<endl;
                
                }

                 }
                   

            
        }
    }

    


};

int main(int argc, char* argv []) {
    string add2hash;
    string lines;
    string wordsinhash;
    int a = 0;
    ifstream inf;
    ifstream qfs;
    int s = atoi(argv[3]);

    string col = argv[4];
    //cout<<"col:"<<col<<endl;
    Bucket b;  
    HashTable hash(s, b);
    //cout<<hash.getsize()<<":size"<<endl;
    //cout<<"HELLOOOO"<<endl;
    if(argc != 5  && argc !=6) exit(1);
    
    if(argc == 6) a = atoi(argv[5]);
       //cout<<"a:"<<a<<endl;
    inf.open(argv[1]);
    qfs.open(argv[2]);

    int l = 0;

    if(inf.is_open() == true){
        int wordnum = 0;
        while(getline(inf, lines)){
            l++;
            wordsinhash = readwords(lines);
            istringstream hw(wordsinhash);

            while( hw >> add2hash){
                wordnum++;
                for(int i =0; i<add2hash.size(); i ++){
                    if(isupper(add2hash[i])){
                    add2hash[i] = tolower(add2hash[i]);
                    }
                }
  
                hash.insert(add2hash, col, l, a);
                
            }

            
            
        }


        

        string look;
        
        int uniques = 0;
        int co = 0;
        
            // for(int i = 0; i < hash.words.size(); i++){
            //     bool match = false;
            //     for(int j = 1; j < hash.words.size(); j++){
            //        if(j == i) j++;
            //        if(j ==  hash.words.size()) break;
            //        if(hash.words.at(i).getkey() == hash.words.at(j).getkey()){
            //                 match = true;
            //                 break;
            //        }

                    
            //     }
            //     if(match == false){
            //        //cout<<uniques<<"&"<<endl;
            //        uniques++;
            //     }
                
            // }

            for(int i =0; i < hash.words.size();i++){
                //cout<<i<<" collisions: "<< hash.words.at(i).getcollisions()<<endl;
                co += hash.words.at(i).getcollisions() * hash.words.at(i).getlines().size();
                if (!hash.words.at(i).empty()) {
                   uniques++;
                }
            }
            //cout<<co<<"$$$$$$$"<<endl;
            cout<<"The number of words found in the file was "<<wordnum<<endl;
            cout<<"The number of unique words found in the file was "<<uniques<<endl;
            cout<<"The number of collisions was "<<co<<endl<<endl;

        while(qfs >> look){
            hash.find(look, col, a);
        }
        
        
    }
    
   return 0;
}
