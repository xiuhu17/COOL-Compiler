int main() {
    int k = 0;
    for (int i = 0; i < 1; ++ i) {
       for (int j = 0; j < 5; ++ j) {
        k ++;
       }
        for (int j = 0; j < 5; ++ j) {
        k ++;
        }
       }
       

    
    for (int i = 0; i < 5; ++ i) {
        for (int j = 0; j < 3; ++ j) {
            k ++;
        }

        for (int j = 0; j < 3; ++ j) {
           for (int p = 0; p < 10; ++ p) {
             ++ k;
           }

           for (int p = 0; p < 10; ++ p) {
             ++ k;
             int x = 0;
             do {
                ++ x;
             }while(x < 20);
           }
        }

        for (int j = 0; j < 3; ++ j) {
           for (int p = 0; p < 10; ++ p) {
             ++ k;
           }

           for (int p = 0; p < 10; ++ p) {
             ++ k;
           }
        }

    }
    for (int i = 0; i < 1; ++ i) {
        ++k;
    }
    
    return k;
}   