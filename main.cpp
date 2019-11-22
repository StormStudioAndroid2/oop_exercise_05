#include <iostream>
#include "Rectangle.h"
#include "./containers/list.h"
#include <string.h>
#include <algorithm>

int main() {
    char str[10];
    containers::list<Rectangle<double> > l;
    auto it = l.begin();
    while(std::cin >> str){
        if(strcmp(str,"push")==0){
            Rectangle<double> rectangle;
            rectangle.scan(std::cin);
            l.add(rectangle);
        }else if(strcmp(str,"delete")==0){
            try {
                int t;
                std::cin >> t;

                std::next(it,t);
                l.erase(l.begin()+t);
                std::cout << "\n";
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        }
        else if(strcmp(str,"front")==0) {
            try {
               l.front().print(std::cout);
                std::cout << "\n";
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        } else if(strcmp(str,"end")==0){
            try {
               
                l.End().print(std::cout);
            }catch (std::exception& ex){
                std::cout <<ex.what() << "\n";
            }
        }else if(strcmp(str,"square")==0) {
            int g;
            std::cin >> g;
            long res=std::count_if(l.begin(),l.end(),[g](Rectangle<double> f){ return f.getSquare() < g;});
            std::cout << res << "\n";
        } else if(strcmp(str,"insert")==0){
            int r;
            std::cin >>r;
            Rectangle<double> rectangle;
            rectangle.scan(std::cin);
            l.insert(l.begin() + r,rectangle);
        }else if(strcmp(str,"all")==0){
            if (l.begin()!=nullptr) {
            std::for_each(l.begin(),l.end(),[](Rectangle<double> f){f.print(std::cout); });
            std::cout<< "\n";
            } else {
                std::cout << "Empty list!" << std::endl;
            }
        }

    }
    return 0;
}