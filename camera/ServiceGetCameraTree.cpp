#include "ServiceGetCameraTree.h"

ServiceGetCameraTree::ServiceGetCameraTree(QObject *parent) : QObject(parent)
{

    timer = new QTimer;
    timer->setSingleShot(true);

    m_cameraTreeModel = new CameraTreeModel();
    //    connect(networkHandler, SIGNAL(sigInternalServerError()), this, SLOT(internalServerError()));

    request();
}

ServiceGetCameraTree::~ServiceGetCameraTree()
{
    //    delete networkHandler;
    delete timer;
    //    delete m_modelGroupingLoadingBills;
}

void ServiceGetCameraTree::request()
{
    emit sigBusyIndicatorShow();


    qDebug() << "request: ";

    QJsonObject qJsonObject;
    //    qJsonObject.insert("type", type);
    //    qJsonObject.insert("startDate", startDate);
    //    qJsonObject.insert("endDate", endDate);

    QJsonDocument qJsonDocument(qJsonObject);
    QString address = "/app/GroupingLoadingBills";

    //remove after get services
    QString filePath = "C:/Users/Morteza/Documents/GitHub/VMS/model/api/camera/cameraTreeJson.json";
    QFile jsonFile(filePath);

    if (!jsonFile.open(QFile::ReadOnly)) {
        qWarning() << "open file failed:" << jsonFile.fileName() << jsonFile.errorString();
    }
    QJsonParseError error;

    QJsonDocument jsonData = QJsonDocument::fromJson(jsonFile.readAll(), &error);

    if (jsonData.isNull()) {
        qWarning() << error.errorString();
    }
    qDebug() << "call responce: " << jsonData;

    responseData(jsonData);
    jsonFile.close();
    //    responseData(file.readAll());
    //    networkHandler->sendRequest(qJsonDocument, address, true);
    //    connect(timer, SIGNAL(timeout()), this, SLOT(serverNotResponce()));
    //    connect(networkHandler, SIGNAL(sigGetReceivedData(QJsonObject *)), this, SLOT(responseData(QJsonObject *)));
    //    connect(networkHandler, SIGNAL(sigGetReceivedMessage(QJsonObject *)), this, SLOT(responseMessage(QJsonObject *)));
    //    timer->start(NetworkHandler::TIMER_INTERVAL);
}

void ServiceGetCameraTree::responseData(QJsonDocument result)
{
    //    m_modelGroupingLoadingBills->removeData();
    //    endOffServiceExecution();

    // message responce

    qDebug() << "result: " << result.object();

    m_cameraTreeModel->loadDataFromJson(result); //callModelData(result.object());
    //                foreach (const QJsonValue & value, (*result)["result"].toObject()["data"].toArray() ) {
    //                    m_modelGroupingLoadingBills->addData(EntityGroupingLoadingBills(value["createDate"].toString(),value["number"].toInt(),
    //                            value["creator"].toString(),value["checked"].toInt()));
    //                }
    emit sigSuccess();


    //    result = nullptr;
}


//void ServiceGetCameraTree::responseMessage(QJsonDocument *result)
//{
//    //    m_modelGroupingLoadingBills->removeData();
//    endOffServiceExecution();

//    QString message = QString();

//    QJsonArray array = (*result)["result"].toObject()["message"].toArray();
//    // message responce
//    if ((*result)["result"].toObject()["code"].toInt() == 2)
//    {
//        foreach (const QJsonValue& value, array) {
//            message += value.toString() ;
//            if(array.count() > 1 )
//                message += "\n";
//        }
//        emit sigReject(message);
//    }
//    // invalid input value
//    else if ((*result)["result"].toInt() == -2)
//    {
//        foreach (const QJsonValue& value, (*result)["message"].toArray()) {
//            message += value.toString() + "\n";
//        }
//        emit sigReject(message);
//    }

//    result = nullptr;
//}

void ServiceGetCameraTree::serverNotResponce()
{
    endOffServiceExecution();
    //    emit sigServerNotResponce(SERVER_NOT_RESPONCE);
}

void ServiceGetCameraTree::internalServerError()
{
    endOffServiceExecution();
    //    emit sigInternalServerError(INTERNAL_SERVER_ERROR);
}

void ServiceGetCameraTree::endOffServiceExecution()
{
    emit sigBusyIndicatorHidden();

    timer->stop();
    disconnect(timer, SIGNAL(timeout()), this, SLOT(serverNotResponce()));
    //    disconnect(networkHandler, SIGNAL(sigGetReceivedMessage(QJsonObject *)), this, SLOT(responseMessage(QJsonObject *)));
    //    disconnect(networkHandler, SIGNAL(sigGetReceivedData(QJsonObject *)), this, SLOT(responseData(QJsonObject *)));
}


