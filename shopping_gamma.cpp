/******************************************************************************/
/* Code done by Ignazio Leotta
/* input are kept in 3 files shopping_list.txt with the items bought, their price each couple per line, 
/*as in the real supermarket bills, 3x2 .txt with the items you can apply the 3x2 discount
/*discitams.txt with the list of items you can buy and get one for 3 every 3
/*the discounts are applied in the following order:
/* 1. Apples for oranges (hahaha)
/* 2. 3x2
/* Buy 3 get the cheapest for free
/*the discounts are mutually exclusives
/*the output is a list of the items with their discounted price, free oranges at the bottom and total
/*
/*let me know if you have problems running it: ignleotta@gmail.com
/*************************************************************************/

#include <iostream>
#include <sstream>
#include <string>
#include <fstream>
#include <vector>
#include <istream>
#include <algorithm>
#include <vector>

/*****************************************/
/*struct for Product
/*
/*****************************************/
struct Product {
    int id;
    std::string name;
    double price;
}P, orange_sale;

bool operator<(const Product& a, const Product& b) {
        return a.price<b.price;
}


int Read_vector_struct (std::vector<Product> & list) {
          for (unsigned i=0; i<list.size(); i++)
                       std::cout<<" prd is: "<<list[i].name<<" price is: "<<list[i].price<<std::endl;
                        return 0;
}


/*******************/
/*Read_lista function to insert a shopping list into a vector
/********************/
std::vector<Product> Read_list(std::istream & is)
{
   std::vector<Product> vec;
   std::string name;
   double price;
   int id=1;
    while (is  >> P.name >> P.price)
         {
          P.id=id;
          vec.push_back(P); //emplace back did not work with g++ 11 
          id++;
      }
   return vec;
}

/*****************************/
/* I thought about making a class with total as protected datatype, since I did not have 
/* much time I just made a function
/****************************/
double Calculate_amount (std::vector<Product> & list) {

    double total=0.0;
    for (std::vector<Product>::iterator ita = list.begin() ; ita != list.end(); ++ita)
     {
      total+=ita->price;
     }
   return total;
}

/* Count_disc and Check_disc are used for the third kind of discount */

std::vector<Product> Count_disc (std::vector<Product> & list) {

std::ifstream infile("disc_items.txt");
//std::cout<<"Ignazio_1"<<std::endl;
  if(infile.fail()){
     std::cout<<"'disc_items.txt' does not exist"<<std::endl;
     return list;
     }
 std::string line;
 std::vector<std::string> disc;
 std::vector<Product> vec_temp;
 std:: string prd;
  while (std::getline(infile,line)) {
    disc.push_back(line);
   }
 // read_vector(disc);
 //     std::cout<<"Ignazio1"<<std::endl;
    for(std::vector<std::string>::iterator it=disc.begin(); it !=disc.end(); it++) {
       prd=*it;
       for (std::vector<Product>::iterator ita = list.begin() ; ita != list.end(); ++ita) {
         if (ita->name==prd) {
              if (ita->price>0)
                vec_temp.push_back(*ita);
             }
          }
     }
  std::sort (vec_temp.begin(),vec_temp.end());

  return vec_temp;
}



std::vector<Product> Check_disc(std::vector<Product> & list, std::vector<Product> & disc) {

    int size=0;
    size=disc.size();
    int  obj_to_disc = size/3;
     if (obj_to_disc>=1) {
          for (int i=0;i<obj_to_disc;i++) {
               for (std::vector<Product>::iterator it = list.begin() ; it != list.end(); ++it) {
                if (it->id==disc[i].id) {
                  if (it->id>0)
                     it->price=0.0;
                   }
                 }
               }
      }
    return list;
}
/*********************************************/
/*function for the buy 2 apples take one orange for free
/*********************************************/

int Check_Orange_sale (std::vector<Product> & list) {

int count=0;
int i=0;
std::string ditem="apple";

//std::cout<<"Ignazio1"<<std::endl;

for (std::vector<Product>::iterator it = list.begin() ; it != list.end(); ++it)
         {
       //   std::cout<<"Ignazio count "<<count<<std::endl;
          if (it->name==ditem) {
          //    if (it->price>0.0)
          count++;
   //        std::cout<<"Ignazio count "<<count<<std::endl;
           }
             if (count==2) {
                 i++;
                 count=0;}
            }
return i;
}

/*********************************************/
/* function for the 3X2 discount
/*********************************************/

std::vector<Product> Check_3per2 (std::vector<Product> & list)
 {
//     std::cout<<"Ignazio List"<<std::endl;
     int count =0;
     int i=0;


std::ifstream infile("disc3x2_items.txt");
if(infile.fail()){
       std::cout<<"'disc3x2_items.txt' does not exist"<<std::endl;
          return list;
}

//std::cout<<"Ignazio_1"<<std::endl;
std::string line;
std::vector<std::string> disc;
std:: string prd;
while (std::getline(infile,line)) {
   disc.push_back(line);
  }
for (unsigned i=0; i<disc.size(); i++) {
     std::string ditem= disc.at(i);
  for (std::vector<Product>::iterator it = list.begin() ; it != list.end(); ++it)
     {  
         if (it->name==ditem) {
             count++;
             if (count==3)
                 it->price=0.0;
             count==0;}
         
         }
    }
return list;
} 

int main ()
{


std::vector<Product> vec;
std::vector<Product> temp;
std::vector<Product> finale;
orange_sale.name="orange";
orange_sale.price=0.0;
int num_oranges_sale=0;


std::ifstream infile("shopping_list.txt");

if(infile.fail()){
       std::cout<<"'shopping_list.txt' does not exist"<<std::endl;
          return 0;
}

 vec = Read_list(infile);

 Check_3per2(vec);
 num_oranges_sale = Check_Orange_sale(vec);
 if (num_oranges_sale>=1) {
     for (int i=0;i<=num_oranges_sale; i++) {
             vec.push_back(orange_sale);
     }
 }


temp=Count_disc(vec);
finale=Check_disc(vec,temp);
Read_vector_struct(finale);
std::cout<<"Total is: "<<Calculate_amount(finale)<<std::endl;
return 0;
}
