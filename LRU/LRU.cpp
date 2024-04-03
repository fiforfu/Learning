#include <iostream>
#include <list>
#include <unordered_map>
#include <utility>

using std::cout;
using std::endl;
using std::list;
using std::unordered_map;
using std::pair;

class LRU
{
public:
    LRU(int cap)
    : _capacity(cap)
    {

    }

    void put(int key, int value)
    {
        auto it = _cache.find(key);
        //该key已经在链表中了
        if(it != _cache.end())
        {
            //更新value
            it->second->second = value;
            //移动key与value在_nodes(list)中的位置
            _nodes.splice(_nodes.begin(), _nodes, it->second);
        }
        else//该key不在链表中
        {
            //如果list是满的
            if(_capacity == (int)_nodes.size())
            {
                //获取list的最后一个元素
                auto &deleteNode = _nodes.back();
                //删除掉最后一个元素
                _nodes.pop_back();
                /* it = _cache.find(deleteNode.first); */
                /* _cache.erase(it); */
                _cache.erase(_cache.find(deleteNode.first));

            }
            //将key与value插入到list的最前面
            _nodes.push_front(pair<int, int>(key, value));
            //同时更新到unordered_map中
            _cache[key] = _nodes.begin();
        }

    }

    int get(int key)
    {
        auto it = _cache.find(key);
        if(it != _cache.end())
        {
            _nodes.splice(_nodes.begin(), _nodes, it->second);
            return it->second->second;
        }
        else
        {
            return -1;
        }
    }

    void print() const
    {
        for(auto &elem : _nodes)
        {
            cout << elem.first << "  " << elem.second << "  ";
        }
        cout << endl;
    }
private:
    int _capacity;//元素的个数
    list<pair<int, int>> _nodes;//存放元素的节点
    unordered_map<int, list<pair<int, int>>::iterator> _cache;
};

void test()
{
    LRU lru(4);
    lru.put(1, 10);
    lru.print();

    cout << endl;
    lru.put(2, 20);
    lru.print();

    cout << endl;
    cout << "lru.get(1) = " << lru.get(1) << endl;
    lru.print();

    cout << endl;
    cout << "lru.get(2) = " << lru.get(2) << endl;
    lru.print();

    cout << endl;
    lru.put(3, 30);
    lru.print();

    cout << endl;
    cout << "lru.get(2) = " << lru.get(2) << endl;
    lru.print();

    cout << endl;
    lru.put(3, 33);
    lru.print();

    cout << endl;
    lru.put(4, 40);
    lru.print();

    cout << endl;
    lru.put(5, 50);
    lru.print();

    cout << endl;
    cout << "lru.get(1) = " << lru.get(1) << endl;
    lru.print();

}

int main(int argc, char *argv[])
{
    test();
    return 0;
}


