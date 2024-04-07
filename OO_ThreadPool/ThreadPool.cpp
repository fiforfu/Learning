#include "ThreadPool.h"
#include "WorkThread.h"
#include "Task.h"

#include <unistd.h>
#include <iostream>
using namespace std;

ThreadPool::ThreadPool(size_t threadNum, size_t queSize)
:_threadNum(threadNum)
,_queSize(queSize)
,_taskQue(_queSize)
,_isExit(false){
    //预留空间
    _threads.reserve(_threadNum);
}

ThreadPool::~ThreadPool(){

}

//线程池的启动与停止
void ThreadPool::start(){
    //创建工作进程
    for(size_t idx = 0;idx != _threadNum; ++idx){
        _threads.push_back(unique_ptr<Thread>(new WorkThread(*this)));
    }

    //将工作线程运行起来
    for(auto &th : _threads){
        th->start();
    }
}

void ThreadPool::stop(){
    //任务如果执行完，就不能让子线程退出
    while(!_taskQue.empty()){
        sleep(1);
    }
    _isExit = true;

    //在回收之前将所有的工作线程唤醒
    _taskQue.wakeup();

    //将工作线程停止
        for(auto &th : _threads){
            th->stop();
        }
}

//添加任务与获取任务
void ThreadPool::addTask(Task *ptask){
    if(ptask){
        _taskQue.push(ptask);
    }
}

Task *ThreadPool::getTask(){
    return _taskQue.pop();
}

//线程池交给工作线程执行的任务
void ThreadPool::doTask(){
    while(!_isExit){
        Task *ptask = getTask();
        if(ptask){
            ptask->process();//执行任务
        }
        else{
            cout << "nullptr == ptask" << endl;
        }
    }
}
