#include <vector>
#include <map>
#include <string>
#include "user"
#include "inventory"

using namespace std;

int main(){
    vector<User> users;
    vector<Gadget> cart;
    vector<Gadget> inventory;
    map<string, int> usermap;

    users = loadUsers();
    inventory = loadInventory();

    int index = 0;
    for(auto user: users){
        usermap[user.email] = index++;
    }

    tuple<string, string> login_cred;

    login_cred = getUser(usermap);

    string username = get<0>(login_cred);
    string pass = get<1>(login_cred);

    auto userItr = usermap.find(username);
    int userIdx = -1;
    if(userItr != usermap.end()){
        userIdx = userItr -> second;
        if (users[userIdx].pass != pass){
            cout << "Username and password doesnot match.\n";
            exit(0);
        }
    }else{
        cout << "User does not exist! Signup to continue" << endl;
        auto user = addUser(username, get<1>(login_cred));
        users.push_back(user);
        usermap[user.email] = index++;
        userIdx = users.size() - 1;
    }
    User user = users[userIdx];
    cout << "------------------------------------" << endl;
    cout << "Welcome back " << user.name << endl;
    cout << "------------------------------------" << endl;
    // User user = 
    int choice = -1;
    do{
        switch(choice){
            case 1:
                listGadgets(inventory);
                break;
            case 2:{
                cout << "------------------------------------" << endl;
                cout << "Enter the Gadget ID:";
                int id;
                cin >> id;
                if(id > inventory.size()) cout << "Invalid Gadget ID \n";
                else cart.push_back(inventory[id - 1]);
                cout << "------------------------------------" << endl;
                break;
            }
            case 3:
                cout << "------------------------------------" << endl;
                if(cart.size() == 0) cout << "You cart is empty\n";
                else{
                    cout << "Your cart: \n";
                    for(auto gd: cart) cout << gd;
                }
                cout << "------------------------------------" << endl;
                break;
            case 4:
                cout << "------------------------------------" << endl;
                cout << "Thank you for shopping! Visit us again!\n";
                cout << "------------------------------------" << endl;
                exit(0);
                break;
            default:
                break;

        }
        cout << "Choose any of the option: " << endl;
        cout << "1. View available gadgets" << endl;
        cout << "2. Add a gadget to cart" << endl;
        cout << "3. Checkout" << endl;
        cout << "4. Exit" << endl;
    }
    while(cin >> choice);
    return 0;
}