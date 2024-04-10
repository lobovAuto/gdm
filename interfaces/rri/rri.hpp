/**
 * Remote repo interface
*/

#pragma once

class Rri
{
private:
    /* data */
public:
    // Rri(/* args */);
    // virtual ~Rri();
    virtual int push() = 0;
    virtual int pull() = 0;
    virtual int check_repo_to_gdm_file() = 0;
    virtual int checkout() = 0;
    virtual int status() = 0;
    virtual int clone() = 0;
};

