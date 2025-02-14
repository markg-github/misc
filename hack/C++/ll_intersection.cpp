
// C++ program to get intersection point of two linked list
// using two nested loops

#include <bits/stdc++.h>
using namespace std;

class Node {
  public:
    int data;
    Node *next;
    Node(int x) {
        data = x;
        next = NULL;
    }
};

/* function to get the intersection point of two linked
lists head1 and head2 */
Node *getIntersectionNode(Node *head1, Node *head2) {
    while (head2 != NULL) {
        Node *temp = head1;
        while (temp) {
          
            // if both Nodes are same
            if (temp == head2)
                return head2;
            temp = temp->next;
        }
        head2 = head2->next;
    }
      
    // intersection is not present between the lists
    return NULL;
}

int main() {

    // Create two linked lists
    // 1st list: 10 -> 15 -> 30
    // 2nd list: 3 -> 6 -> 9 -> 15 -> 30
    // 15 is the intersection point

    // creation of first list
      Node *head1 = new Node(10);
    head1->next = new Node(15);
    head1->next->next = new Node(30);

    // creation of second list
      Node *head2 = new Node(3);  
      head2->next = new Node(6);
    head2->next->next = new Node(9);
    head2->next->next->next = head1->next;

    Node *intersectionPoint = getIntersectionNode(head1, head2);

    if (intersectionPoint == NULL)
        cout << " No Intersection Point \n";
    else
        cout << "Intersection Point: " << intersectionPoint->data << endl;
}
