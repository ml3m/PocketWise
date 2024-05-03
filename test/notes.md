
usage:

    sha256 * algorithm = new sha256;
    std::string hashPassword = algorithm->doSha256(passwordStr);
    delete algorithm;
