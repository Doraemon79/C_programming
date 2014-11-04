    #include <sstream>
    #include <string>
    #include <vector>
    #include <stdlib.h>
    #include <iostream>
    #include <fstream>
    #include <algorithm>
    #include <iterator>
    #include<iomanip>

  double Calculate_Best_Option (std::vector<double> &v1) {
    
              
    std::vector<int>::iterator it;
    double Cookies=v1[0];
    int n=0;
    double Farm=v1[1];
    double Target=v1[2];
    int max_absurd=Target;
    long double Act_Prod=2;       
    long double Start_time=Target/Act_Prod;
    long double Starter=0;
    long double New_Time=0;
          
     while ( n<= max_absurd) {
        Act_Prod=2+(n*Farm);
        n++;
        long double New_Prod=2+(n*Farm);
        New_Time=Starter+(Target/New_Prod)+(Cookies/Act_Prod);
        if (New_Time>=Start_time)
        break;

        Starter=Starter+Cookies/Act_Prod;
        Start_time=New_Time;
         }  
    return Start_time;
 }


int main() {
    
int num_case=0;
std::string str; 
std::vector <double> vec;
std::string line;

std::cout.precision(9);

    double val=0.000000;

    std::ifstream infile("B-large.in");
    std::getline(infile,line);
    std::stringstream ss(line);
    std::vector<int>::iterator it;
    ss>>num_case;
    
    
    for (int i=0; i<num_case; i++) {

            std::getline(infile,line);
           
            std::stringstream st(line);
            //st.precision(6);
            while(st >> val) //Extract integers from line
            vec.push_back(val);
              
              
            std::cout.precision(7);
            std::cout<<"Case #"<<i+1<<": "<<std::fixed<<std::setprecision(10)<<Calculate_Best_Option(vec)<<std::endl;
            vec.clear();
            
    }
    return 0;
}
