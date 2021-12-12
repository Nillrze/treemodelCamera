#ifndef TREENODE_H
#define TREENODE_H

#include <QList>
#include <QObject>
#include <QVariant>

class TreeNode {
public:
    explicit TreeNode(TreeNode *parent = nullptr) : mParent(parent) {}
    ~TreeNode() {
        qDeleteAll(mChildrenList);
    }

    void appendChild(TreeNode *child) {
        mChildrenList.append(child);
    }
    void removeChild(TreeNode *child) {
        if(mChildrenList.removeOne(child)) {
            //删除成功时释放
            delete child;
        }
    }
    void appendData (const QVariant &data) { mDatas.append(data);}

    //请确保0 <= index < dataCount。
    void setData(int index, const QVariant &data) {mDatas[index] = data;}
    TreeNode *child(int index) const { return mChildrenList.value(index);}
    TreeNode *parent() const { return mParent;}
    int childCount() const { return mChildrenList.count();}
    QVariant data(int index) const { return mDatas.at(index);}
    int dataCount() const {return mDatas.count();}
private:
    QVector<QVariant> mDatas;
    TreeNode *mParent = nullptr;
    QList<TreeNode *> mChildrenList;
};

#endif // TREENODE_H
