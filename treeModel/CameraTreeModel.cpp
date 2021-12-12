#include "CameraTreeModel.h"

CameraTreeModel::CameraTreeModel(QObject *parent) : QAbstractItemModel(parent)
{

    mRoleNameMap[TreeModelRoleName]   = "name";
    mRoleNameMap[TreeModelRoleDetail] = "detail";
    mRoleNameMap[TreeModelRoleIcon]   = "icon";
    mRoleNameMap[TreeModelRoleType]   = "type";
    mRootNode = new TreeNode;
    mRootNode->appendData("");
    mRootNode->appendData("");
}
CameraTreeModel::~CameraTreeModel() {
    delete mRootNode;
    mRootNode = nullptr;
}
void addArrayToTree (TreeNode *node, const QJsonArray &array) {
    TreeNode *newNode = nullptr;
    QJsonArray subArray;
    for (const auto &i : array) {
        auto obj = i.toObject();
        newNode = new TreeNode(node);
        newNode->appendData(obj["name"].toVariant());
        newNode->appendData(obj["detail"].toVariant());
        newNode->appendData(obj["icon"].toVariant());
        newNode->appendData(obj["type"].toVariant());
        node->appendChild(newNode);
        subArray = obj["childrenclass"].toArray();
        if (!subArray.isEmpty()) {
            addArrayToTree(newNode, subArray);
        }
    }
}
void addTreeToArray (const TreeNode *node, QJsonArray &array) {
    if (node) {
        QJsonObject obj;
        if (node->dataCount() >= 2) {
            obj["name"]   = node->data(0).toString();
            obj["detail"] = node->data(2).toString();
            obj["icon"]   = node->data(3).toString();
            obj["type"]   = node->data(4).toString();
        }
        int count = node->childCount();
        if (count > 0) {
            QJsonArray arr;
            for (int i = 0; i < count; ++i) {
                addTreeToArray(node->child(i), arr);
            }
            obj["childrenclass"] = arr;
        }
        array.append(obj);
    }
}

QString CameraTreeModel::loadDataFromJson(const QJsonDocument &jsonDoc) {

    auto rootObj = jsonDoc.object();
    const auto & array = rootObj.value("data").toArray();
    emit beginResetModel();
    addArrayToTree(mRootNode, array);
    emit endResetModel();
    return QString();
}

TreeNode *CameraTreeModel::getNode(const QModelIndex &index) const {
    if (index.isValid()) {
        auto node = static_cast<TreeNode *>(index.internalPointer());
        if (node) {
            return node;
        }
    }
    return mRootNode;
}

QVariant CameraTreeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QModelIndex();
    }
    if (role == TreeModelRoleName || role == TreeModelRoleDetail ||
            role == TreeModelRoleIcon || role == TreeModelRoleType) {
        auto node = getNode(index);
        return node->data(role - TreeModelRoleName);
    } else {
        return QVariant();
    }
}

QModelIndex CameraTreeModel::index(int row, int column, const QModelIndex &parent) const {
    if (parent.isValid() && parent.column() != 0) {
        return QModelIndex();
    }
    auto parentNode = getNode(parent);
    auto childNode = parentNode->child(row);
    if (childNode) {
        return createIndex(row, column, childNode);
    } else {
        return QModelIndex();
    }
}

QModelIndex CameraTreeModel::parent(const QModelIndex &child) const {
    if (!child.isValid()) {
        return QModelIndex();
    }
    auto childNode = getNode(child);
    auto parentNode = childNode->parent();
    if (parentNode == mRootNode) {
        return QModelIndex();
    }
    return createIndex(parentNode->childCount(), 0, parentNode);
}

int CameraTreeModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent)
    return mRootNode->dataCount();
}
int CameraTreeModel::rowCount(const QModelIndex &parent) const {
    return getNode(parent)->childCount();
}

bool CameraTreeModel::hasChildren(const QModelIndex &parent) const {
    if (!parent.isValid()) return false;
    auto node = getNode(parent);
    if (node) {
        return node->childCount() > 0;
    } else {
        return false;
    }
}

bool CameraTreeModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole) return false;
    TreeNode *node = getNode(index);
    auto column = index.column();
    if (column < node->dataCount()) {
        node->setData(column, value);
        emit dataChanged(index, index);
        return true;
    } else {
        return false;
    }
}

QHash<int, QByteArray> CameraTreeModel::roleNames() const {
    return mRoleNameMap;
}

Qt::ItemFlags CameraTreeModel::flags(const QModelIndex &index) const {
    if (!index.isValid()) return 0;
    return QAbstractItemModel::flags(index) | Qt::ItemIsEditable;
}

