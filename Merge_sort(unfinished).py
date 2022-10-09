import time      
def merge_sort(list):
    print(list)
    if len(list) == 1:
        return list
    left = merge_sort(list[:len(list)//2])
    right = merge_sort(list[len(list)//2:])
    return merge(left,right)

def merge(left,right):
    list_ = []
    left_count = 0
    right_count = 0
    try:
        while True:
            if left[left_count] > right[right_count]:
                list_.append(right[right_count])
                right_count+=1
            else:
                list_.append(left[left_count])
                left_count+=1
    except:
        return list_ + left[left_count:] + right[right_count:]

st = time.time()

list = [5,3,2,6,1,10,0,8]
print(merge_sort(list))


elapsed_time = time.time() - st
print("Run time of programe:", elapsed_time * 1000)
Neznasssss
