CREATE DATABASE apm;

USE apm;

CREATE TABLE usuario (
    id int NOT NULL AUTO_INCREMENT,
    email varchar(128) UNIQUE NOT NULL,
    senha varchar(128),
    PRIMARY KEY(id)
);

CREATE TABLE aluno (
    id int NOT NULL AUTO_INCREMENT,
    nome varchar(128) NOT NULL,
    email varchar(128) NOT NULL,
    cpf char(11) NOT NULL,
    sexo char(1) NOT NULL,
    estado char(2) NOT NULL,
    PRIMARY KEY(id)
);

# DADOS TESTE
INSERT INTO usuario (email, senha) VALUES ('admin', 'admin');
INSERT INTO aluno (nome, email, cpf, sexo, estado) VALUES ('Nobuo', 'uematsu@udesc.br', '78998778958', 'm', 'SC');

# DROP
DROP TABLE aluno;
DROP TABLE usuario;

DROP DATABASE apm;
