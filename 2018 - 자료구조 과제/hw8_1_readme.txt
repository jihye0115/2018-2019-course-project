이 코드는 원하는 위치에 값을 집어넣은 후, min heap을 유지하도록 정렬해줍니다.
함수 Decrease_key_min_heap와 Increase_key_min_heap 총 2개로 이루어져있습니다.
함수 Decrease_key_min_heap는 대입된 값이 원래 위치의 값보다 작은 경우 호출되는 함수로,
그 위치의 노드부터 부모 노드로 향하며 값을 비교하고, min heap으로 정렬해줍니다.
함수 Increase_key_min_heap는 대입된 값이 원래 위치의 값보다 큰 경우 호출되는 함수로,
그 위치의 노드부터 자식 노드로 향하며 값을 비교하고, min heap으로 정렬해줍니다.

원래 노드의 값보다 큰 값을 대입하고 싶은 경우, Increase_key_min_heap(h,위치,값);을 호출하면 됩니다.
원래 노드의 값보다 작은 값을 대입하고 싶은 경우, Decrease_key_min_heap(h,위치,값);을 호출하면 됩니다.