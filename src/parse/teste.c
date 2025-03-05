CORRIGIR TESTES


echo "O meu user é $USER e estou em $PWD" -> correto : O meu user é rafael e estou em /home/rafael
echo "$HOME$USER" -> correto : /home/rafaelrafael
echo "$HOME$NAO_EXISTE" -> correto : /home/rafael
echo "User: $USER, Desconhecido: $NAO_EXISTE" -> correto : User: rafael, Desconhecido:

echo $123ABC -> bash -> 23ABC
            -> zsh -> zsh: command not found: 23ABC
            outros(nos) -> \n 

echo $HOME!USER -> bash -> bash: !USER: event not found
                -> ZSH -> zsh: event not found: USER
                outros(nos) -> /home/rafael!USER


echo "'$HOME'" -> correto -> '/home/rafael'
echo "asd"'$HOME'"asd" -> asd$HOMEasd
 echo "Inicio"'$PWD'"Fim" -> Inicio$PWDFim

