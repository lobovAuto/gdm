/**
 * Remote repo interface
*/

#pragma once

class Rri
{
private:
    /* data */
public:
    Rri(/* args */);
    ~Rri();
    virtual int push() = 0;
    virtual int pull() = 0;
    virtual int check_repo_to_gdm_files() = 0;
    virtual int checkout() = 0;
    virtual int status() = 0;
};

