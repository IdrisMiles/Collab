#ifndef RIG_H
#define RIG_H

#include <vector>
#include <memory>

class Bone;

class Rig
{
public:
    Rig();
    virtual ~Rig() {};

    std::shared_ptr<Bone> m_rootBone;
    //std::vector<Bone> m_bones;

};

#endif // RIG_H
