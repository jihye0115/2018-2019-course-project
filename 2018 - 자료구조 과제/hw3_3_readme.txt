이 코드는 다양한 리스트의 연산을 실행해줍니다.

void init(ListType *plist); 
이 함수는 plist가 가리키는 리스트를 초기화해줍니다. 이 함수를 사용하기 위해 리스트의 주소를 보내주면 됩니다.

int is_empty(ListType *plist); 
이 함수는 plist가 가리키는 리스트가 비어있는지 테스트해줍니다.
비어있다면 1, 비어있지 않다면 0을 도출합니다. 이 함수를 사용하기 위해 리스트의 주소를 보내주면 됩니다.

ListNode *get_node_at(ListType *plist, int pos);
이 함수는 plist가 가리키는 리스트의 pos에 해당하는 node의 주소를 도출해줍니다.
이 함수를 사용하기 위해 리스트의 주소와 구하고 싶은 node의 위치를 보내주면 됩니다.

void add_first(ListType *plist, int a);
이 함수는 plist가 가리키는 리스트의 맨 앞에 데이터 a를 가진 노드를 생성하여줍니다.
이 함수를 사용하기 위해 리스트의 주소와 넣을 노드의 데이터를 보내주면 됩니다.

void add_last(ListType *plist, int a);
이 함수는 plist가 가리키는 리스트의 마지막에 데이터 a를 가진 노드를 생성하여줍니다.
이 함수를 사용하기 위해 리스트의 주소와 넣을 노드의 데이터를 보내주면 됩니다.

void add(ListType *plist, int position, element data);
이 함수는 plist가 가리키는 리스트의 pos에 데이터 data를 가진 노드를 생성하여줍니다.
이 함수를 사용하기 위해 리스트의 주소와 넣을 노드의 위치 및 데이터를 보내주면 됩니다.

void display(ListType *plist);
이 함수는 plist가 가리키는 리스트를 화면에 출력해줍니다.
이 함수를 사용하기 위해 리스트의 주소를 보내주면 됩니다.

void del(ListType *plist, int pos);
이 함수는 plist가 가리키는 리스트의 pos에 위치하는 노드를 삭제해줍니다.
이 함수를 사용하기 위해 리스트의 주소와 삭제할 노드의 위치를 보내주면 됩니다.

void delete_first(ListType *plist);
이 함수는 plist가 가리키는 리스트의 첫번째 노드를 삭제해줍니다.
이 함수를 사용하기 위해 리스트의 주소를 보내주면 됩니다.

void delete_last(ListType *plist);
이 함수는 plist가 가리키는 리스트의 마지막 노드를 삭제해줍니다.
이 함수를 사용하기 위해 리스트의 주소를 보내주면 됩니다.

int is_in_list(ListType *plist, element item);
이 함수는 plist가 가리키는 리스트에 item이라는 데이터가 존재하는지 테스트해줍니다. 
존재하면 1, 존재하지 않으면 0을 도출해줍니다.
이 함수를 사용하기 위해 리스트의 주소와 찾고싶은 데이터를 보내주면 됩니다.

int get_entry(ListType *plist, int pos);
이 함수는 plist가 가리키는 리스트의 pos위치에 해당하는 데이터를 도출해줍니다.
이 함수를 사용하기 위해 리스트의 주소와 구하고 싶은 노드의 위치를 구해주면 됩니다.

위의 함수를 마음껏 사용할 수 있습니다. main에서 원하는 만큼 호출하면 됩니다.