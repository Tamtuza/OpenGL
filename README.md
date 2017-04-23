# Como executar os projetos com OPENGL:

1. Faça o download do projeto que quer utilizar

2. Dentro da pasta do projeto, procure a pasta "Debug" e execute o arquivo de extensão ".exe" (ex: "HelloWorldGL.exe")

Caso queira fazer modificações, abra o arquivo de extensão .sln para visualizá-lo no Visual Studio e siga os passos 1, 2 e 3 na seção de configuração do OPENGL logo abaixo

# Como criar e/ou configurar seu projeto OPENGL no Visual Studio:

__Criar:__

1. Abra o Visual Studio e crie um novo projeto vazio 
	File > New > Project > Visual C++ > Empty Project
	Defina um nome para o projeto (ex: "HelloWorld") e clique em 'OK'

2. No 'Solution Explorer' (normalmente na lateral direita), clique com o botão direito sobre a opção 'Source Files', e em seguida selecione Add > New Item

3. Na janela que abrir, selecione 'C++ file', nomeie o arquivo (ex: "main.cpp") e clique em 'Add'

__Configurar__:

1. Baixe a [GLUT](http://www.aerstudio.com.br/downloads/GLUT/GLUT.zip) e descompacte o arquivo dentro da pasta do seu projeto, de preferência no mesmo local onde ficará o arquivo executável

2. Com o projeto aberto no Visual Studio clique em
	Project > Properties > C/C++ > Additional Include Directories, e inclua o endereço da pasta GLUT (ex: "/GLUT")

3. Ainda em Project > Properties vá na opção Linker > Additional Library Directories, e inclua o endereço da pasta lib que se encontra dentro da pasta GLUT (ex: "/GLUT/lib")

4. No Windows Explorer, copie para a pasta Debug ou Release do seu projeto o arquivo "glut32.dll" que se encontra na pasta GLUT, ou copie a dll na pasta "System32" ou "SysWOW64"

5. Inclua a GLUT em seu código "#include <GL/glut.h>"

__ps.:__ ao transportar o executável do projeto, lembre-se de sempre transportar a "glut32.dll" junto, caso contrário o mesmo não irá funcionar
