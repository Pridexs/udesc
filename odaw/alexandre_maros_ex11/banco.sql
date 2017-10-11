CREATE DATABASE apm;

USE apm;

CREATE TABLE usuario (
    email varchar(100) NOT NULL,
    senha varchar(255),
    descricao varchar(1023),
    idade char(10) NOT NULL,
    receber_emails tinyint(1) NOT NULL,
    PRIMARY KEY(email)
);

CREATE TABLE veiculos (
    email_usuario varchar(100) NOT NULL,
    tipo_veiculo char NOT NULL,
    FOREIGN KEY(email_usuario) REFERENCES usuario(email),
    UNIQUE KEY (email_usuario, tipo_veiculo)
);

INSERT INTO usuario (email, senha, descricao, idade, receber_emails) VALUES ('alehstk@gmail.com', 'abc123', 'Uma descrição', 'mais18', 1);
INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES ('alehstk@gmail.com', 'c');
INSERT INTO veiculos (email_usuario, tipo_veiculo) VALUES ('alehstk@gmail.com', 'b');

INSERT INTO usuario (email, senha, descricao, idade, receber_emails) VALUES ('blabla@gmail.com', 'abc123', 'Uma outra descrição um pouco maior', 'mais18', 1);

DROP TABLE veiculos;
DROP TABLE usuario;

DROP DATABASE apm;
