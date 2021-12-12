#ifndef CAMERATREEMODEL_H
#define CAMERATREEMODEL_H

#include <QObject>
#include <QAbstractItemModel>
#include <QFile>
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>

#include "TreeNode.h"

class CameraTreeModel : public QAbstractItemModel {
    Q_OBJECT

public:
    enum TreeModelRoles {
        TreeModelRoleName = Qt::UserRole + 1,
        TreeModelRoleDetail,
        TreeModelRoleIcon,
        TreeModelRoleType
    };
    explicit CameraTreeModel(QObject *parent = nullptr);
    ~CameraTreeModel();
    Q_INVOKABLE QString loadDataFromJson(const QJsonDocument &jsonDoc);

public:
    QVariant data(const QModelIndex &index, int role) const override;
    QModelIndex index(int row, int column, const QModelIndex &parent) const override;
    QModelIndex parent(const QModelIndex &child) const override;
    int columnCount(const QModelIndex &parent) const override;
    int rowCount(const QModelIndex &parent) const override;
    bool hasChildren(const QModelIndex &parent) const override;

    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QHash<int, QByteArray> roleNames() const override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;

protected:
    TreeNode *getNode(const QModelIndex &index) const;

private:
    TreeNode *mRootNode = nullptr;
    QHash<int, QByteArray> mRoleNameMap;
};

#endif // CAMERATREEMODEL_H
