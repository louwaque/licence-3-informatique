CREATE TABLE EnsemblesAttributs (
    NumEnsAtt INTEGER NOT NULL PRIMARY KEY
);

CREATE TABLE EnsembleContientAtribut (
    NumEnsAtt INTEGER NOT NULL,
    NomAtt VARCHAR(30) NOT NULL,
    CONSTRAINT PK_EnsAtt PRIMARY KEY (NumEnsAtt, NomAtt),
    CONSTRAINT FK_EnsAtt_NumEnsAtt FOREIGN KEY(NumEnsAtt) REFERENCES EnsemblesAttributs(NumEnsAtt) ON DELETE CASCADE
);

create sequence NumEnsAtt;


CREATE TABLE DFs (
    NumDF INTEGER PRIMARY KEY,
    NumEnsGauche INTEGER NOT NULL REFERENCES EnsemblesAttributs(NumEnsAtt),
    NumEnsDroit INTEGER NOT NULL REFERENCES EnsemblesAttributs(NumEnsAtt),
    UNIQUE (NumEnsGauche, NumEnsDroit)
);

create sequence NumDF;


CREATE TABLE EnsemblesDFs (
    NumEnsDF INTEGER PRIMARY KEY
);

CREATE TABLE EnsembleContientDF (
    NumEnsDF INTEGER REFERENCES EnsemblesDFs(NumEnsDF),
    NumDF INTEGER REFERENCES DFs(NumDF),
    PRIMARY KEY (NumEnsDF, NumDF)
);

create sequence NumEnsDF;

CREATE TABLE Schemas (
    NumSchema INTEGER PRIMARY KEY,
    NumEnsAtt INTEGER NOT NULL REFERENCES EnsemblesAttributs(NumEnsAtt),
    NumEnsDF INTEGER NOT NULL REFERENCES EnsemblesDFs(NumEnsDF)
);

create sequence NumSchema;
