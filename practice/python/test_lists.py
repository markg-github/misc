
import pdb

class Node:
    def __init__(self, data):
        self.data = data
        self.next = None


# class Node {
#   public:
#     int data;
#     Node *next;
#     Node(int x) {
#         data = x;
#         next = NULL;
#     }
# };

def get_test_list(which_list):
  pdb.set_trace()
  head = None
  p1 = Node(1)
  p2 = Node(1)
  p3 = Node(1)
  p4 = Node(1)
  p5 = Node(1)
  p6 = Node(1)
  p7 = Node(1)
  p8 = Node(1)

  if which_list == 1:
    head = p1
    p1.next = p2
    p2.next = p3
    p3.next = p4
  elif which_list == 2:
    head = p1
    p1.next = p2
    p2.next = p3
    p3.next = p2
  elif which_list == 3:
    head = p1
    p1.next = p2
    p2.next = p3
    p3.next = p4
    p4.next = p5
    p5.next = p6
    p6.next = p7
  elif which_list == 4:
    head = p1
    p1.next = p2
    p2.next = p3
    p3.next = p4
    p4.next = p5
    p5.next = p6
    p6.next = p7
    p7.next = p8
    p8.next = p7

  return head


    # struct ll_node *p3 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p6 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p9 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p10 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p15 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p30 = (struct ll_node *)malloc(sizeof(struct ll_node));

    # p3->value = 3;
    # p3->next = p6;

    # p6->value = 6;
    # p6->next = p9;

    # p9->value = 9;
    # p9->next = p15;

    # p10->value = 10;
    # p10->next = p15;

    # p15->value = 15;
    # p15->next = p30;

    # p30->value = 30;
    # p30->next = NULL;



    # // Create two linked lists
    # // 1st list: 10 -> 15 -> 30
    # // 2nd list: 3 -> 6 -> 9 -> 15 -> 30
    # // 15 is the intersection point

    # // creation of first list
    #   Node *head1 = new Node(10);
    # head1->next = new Node(15);
    # head1->next->next = new Node(30);

    # // creation of second list
    #   Node *head2 = new Node(3);  
    #   head2->next = new Node(6);
    # head2->next->next = new Node(9);
    # head2->next->next->next = head1->next;


    # struct ll_node *p3 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p6 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p9 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p10 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p15 = (struct ll_node *)malloc(sizeof(struct ll_node));
    # struct ll_node *p30 = (struct ll_node *)malloc(sizeof(struct ll_node));

    # p3->value = 3;
    # p3->next = p6;

    # p6->value = 6;
    # p6->next = p9;

    # p9->value = 9;
    # p9->next = p15;

    # p10->value = 10;
    # p10->next = p15;

    # p15->value = 15;
    # p15->next = p30;

    # p30->value = 30;
    # p30->next = NULL;

