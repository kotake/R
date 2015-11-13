//
//  csv_to_transaction.cpp
//  
//
//  Created by 岡響 on 2015/11/10.
//
//

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using namespace std;
int main()
{
    ifstream ifs("iris.csv");
    string str;
    //string label;
	//vector<char> label[];
    //double youso[];
    int count = 0;
    int i;
    double sum;
    double avl;
    
    ofstream ofs("transaction.txt");

    
    if (ifs.fail())
    {
        cerr << "失敗" << endl;
        return -1;
    }
    
    
    getline(ifs,str);
	string tmp;
	istringstream stream(str);
	while(getline(stream,tmp,','))
    {
		count++;
    }
    
    cout << count << endl; 
    double youso[count];
	string label[count];

	string tmp2;
	istringstream stream2(str);
	i = 0;
	while(getline(stream2,tmp2,','))
    {
		label[i] = tmp2;
		i++;
    }

    while(getline(ifs,str))
    {
		i = 0;
		sum = 0;
		string tmp;
        istringstream stream(str);
        while(getline(stream,tmp,','))
        {
            stringstream ss;
            ss << tmp;
            ss >> youso[i];
            i++;
        }
        
        for (i = 0; i < count; i++) {
            sum += youso[i];
        }
        
        avl = sum / count;
        cout << avl << endl; 
        for (i = 0; i < count; i++) {
            if(youso[i] >= avl){
        		//cout << "true" << endl;        
                ofs << label[i];
                ofs << ",";
            }
        }
        
        ofs << endl;
        
    }
    

    return 0;
}
