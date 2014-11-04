


calculate_perfect_click (std::vector<double> &v1) {
           
           int row=v1[0];
           int column=v1[1];
            
            
            
}

int main() {


vector< vector<int> > vec(4, vector<int>(4));

    std::ifstream infile("B-large.in");
    std::getline(infile,line);
    std::stringstream ss(line);
    ss>>num_case;
    
    
    for (int i=0; i<num_case; i++) {
    
                std::getline(infile,line);
                std::stringstream st(line);
                while(st >> val) //Extract integers from line
                vec.push_back(val);
                
                calculate_perfect_click(vec);
                vec.clear();
                return 0;
                
                
}