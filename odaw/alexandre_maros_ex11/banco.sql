CREATE DATABASE apm;

USE apm;

CREATE TABLE usuario (
    id int NOT NULL AUTO_INCREMENT,
    email varchar(255),
    senha varchar(255),
    descricao varchar(1023),
    idade char(10) NOT NULL,
    receber_emails tinyint(1) NOT NULL,
    PRIMARY KEY(id)
);

CREATE TABLE veiculos (
    id_usuario int NOT NULL,
    tipo_veiculo char NOT NULL,
    FOREIGN KEY(id_usuario) REFERENCES usuario(id),
    UNIQUE KEY (id_usuario, tipo_veiculo)
);

INSERT INTO usuario (email, senha, descricao, idade, receber_emails) VALUES ('alehstk@gmail.com', 'abc123', 'Uma descrição', 'mais18', 1);
INSERT INTO veiculos (id_usuario, tipo_veiculo) VALUES (1, 'c');
INSERT INTO veiculos (id_usuario, tipo_veiculo) VALUES(1, 'b');

DROP TABLE veiculos;
DROP TABLE usuario;

DROP DATABASE apm;
