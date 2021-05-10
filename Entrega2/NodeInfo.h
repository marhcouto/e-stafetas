//
// Created by marhc on 10/05/2021.
//

#ifndef ENTREGA2_NODEINFO_H
#define ENTREGA2_NODEINFO_H

typedef enum {RECHARGE, DELIVERY, PICKUP, NONE} interest;

class NodeInfo {
    const int nodeID;
    double latitude{};
    double longitude{};
    interest type;
public:
    NodeInfo(double latitude, double longitude, int nodeID) : latitude(latitude), longitude(longitude), nodeID(nodeID) {};
    explicit NodeInfo(int nodeID) : nodeID(nodeID) {};

    double getLatitude() const {
        return latitude;
    }
    void setLatitude(double latitude) {
        NodeInfo::latitude = latitude;
    }
    double getLongitude() const {
        return longitude;
    }
    void setLongitude(double longitude) {
        NodeInfo::longitude = longitude;
    }
    interest getType() const {
        return type;
    }
    void setType(interest type) {
        NodeInfo::type = type;
    }
    int getNodeID() const {
        return nodeID;
    }

    bool operator==(NodeInfo& nodeInfo) const {
        return this->getNodeID() == nodeInfo.getNodeID();
    }
};


#endif //ENTREGA2_NODEINFO_H
