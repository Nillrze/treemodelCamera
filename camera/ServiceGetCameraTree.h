#ifndef SERVICEGETCAMERATREE_H
#define SERVICEGETCAMERATREE_H

#include <QTimer>
#include <QString>
#include <QObject>
#include <QJsonObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QDebug>

#include <QFile>

#include "../../treeModel/CameraTreeModel.h"

class ServiceGetCameraTree : public QObject
{
    Q_OBJECT
public:
    explicit ServiceGetCameraTree(QObject *parent = nullptr);
    ~ServiceGetCameraTree();
    Q_INVOKABLE void request();

    CameraTreeModel* cameraTreeModel() const
    {
        return m_cameraTreeModel;
    }

private:

    Q_PROPERTY(CameraTreeModel* cameraTreeModel READ cameraTreeModel WRITE setCameraTreeModel NOTIFY cameraTreeModelChanged)

    QTimer* timer;

    CameraTreeModel* m_cameraTreeModel;

public slots:

    void responseData(QJsonDocument result);
//    void responseMessage(QJsonDocument *result);
    void serverNotResponce();
    void internalServerError();
    void endOffServiceExecution();

    void setCameraTreeModel(CameraTreeModel* cameraTreeModel)
    {
        if (m_cameraTreeModel == cameraTreeModel)
            return;

        m_cameraTreeModel = cameraTreeModel;
        emit cameraTreeModelChanged(m_cameraTreeModel);
    }

signals:
    void sigBusyIndicatorShow();
    void sigBusyIndicatorHidden();
    void sigSuccess();
    void sigReject(QString message);
    void sigServerNotResponce(QString message);
    void sigInternalServerError(QString message);
    void cameraTreeModelChanged(CameraTreeModel* treeModel);

};

#endif // SERVICEGETCAMERATREE_H
