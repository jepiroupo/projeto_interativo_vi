dados = {

    labirinto: function (xml){
        //<background>
        width = [], height = [],

        $(xml).find("parede").each(function()
        {
            $('<li class="caminho" style="background-image: url(\'imgs/paredes.png\')"></li>').appendTo('#lista');

        });

        var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

        $("#lista").width(String(width[0]).split("px").join("") * numLis);

        init();
    }
}

function init () {

    $("#lista").find("li").click(listaClick);

    var numLis = 0;
        $("#lista").find("li").each(function(){
            numLis += 1;
        });

    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();
        //console.log("left: " + pos.left + " top: " + pos.top);
        if (pos.left == 0 || pos.left == 1600 || pos.top == 0 || pos.top == 1184){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
    }

    function listaClick (e) {
        e.preventDefault();

        navigate($(this).index());
    }

    function navigate(id){
        var button =  $("#lista").find("li")[id];

        if ($(button).hasClass('caminho')){
            $(button).removeClass('caminho');
            $(button).addClass('parede');
        }
        else if ($(button).hasClass('parede')){
            $(button).removeClass('parede');
            $(button).addClass('vermelho');
        }
        else if ($(button).hasClass('vermelho')){
            $(button).removeClass('vermelho');
            $(button).addClass('azul');
        }
        else if ($(button).hasClass('azul')){
            $(button).removeClass('azul');
            $(button).addClass('verde');
        }
        else if ($(button).hasClass('verde')){
            $(button).removeClass('verde');
            $(button).addClass('amarelo');
        }
        else if ($(button).hasClass('amarelo')){
            $(button).removeClass('amarelo');
            $(button).addClass('caminho');
        }

        var pos = $(button).offset();
        console.log("left: " + pos.left + " top: " + pos.top);
    }
}

var string;
string = "";

var stringXML;
stringXML = "<dados>\r\n";

function gerarXML(){

    var numLis = 0;
    $("#lista").find("li").each(function(){
        numLis += 1;
    });
    for (i=0; i < numLis; i++){
        var button =  $("#lista").find("li")[i];
        var pos = $(button).offset();

        if ($(button).hasClass('caminho')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "0" + "\r\n";//caminho
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "0" + "\r\n";//caminho
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "0" + "\r\n";//caminho
            }else{
                string += pos.left + "" + pos.top + "" + "0" + "\r\n";//caminho
            }
            stringXML += "<info> \r\n";
            stringXML += "<classe>caminho</classe> \r\n";
            stringXML += "<left>"+pos.left+"</left> \r\n";
            stringXML += "<top>"+pos.top+"</top> \r\n";
            stringXML += "</info> \r\n"
        }
        else if ($(button).hasClass('parede')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "1" + "\r\n";//parede
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "1" + "\r\n";//parede
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "1" + "\r\n";//parede
            }else{
                string += pos.left + "" + pos.top + "" + "1" + "\r\n";//parede
            }
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>parede</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('vermelho')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "2" + "\r\n";//vermelho
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "2" + "\r\n";//vermelho
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "2" + "\r\n";//vermelho
            }else{
                string += pos.left + "" + pos.top + "" + "2" + "\r\n";//vermelho
            }
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>vermelho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('azul')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "3" + "\r\n";//azul
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "3" + "\r\n";//azul
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "3" + "\r\n";//azul
            }else{
                string += pos.left + "" + pos.top + "" + "3" + "\r\n";//azul
            }
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>caminho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('verde')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "4" + "\r\n";//verde
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "4" + "\r\n";//verde
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "4" + "\r\n";//verde
            }else{
                string += pos.left + "" + pos.top + "" + "4" + "\r\n";//verde
            }
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>caminho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
        else if ($(button).hasClass('amarelo')){
            if (pos.left > 0 && pos.left < 10){
                string += "000" + pos.left + "" + pos.top + "" + "5" + "\r\n";//amarelo
            }else if (pos.left > 10 && pos.left < 100){
                string += "00" + pos.left + "" + pos.top + "" + "5" + "\r\n";//amarelo
            }else if (pos.left > 100 && pos.left < 1000){
                string += "0" + pos.left + "" + pos.top + "" + "5" + "\r\n";//amarelo
            }else{
                string += pos.left + "" + pos.top + "" + "5" + "\r\n";//amarelo
            }
            stringXML += "\t<info> \r\n";
            stringXML += "\t\t<classe>caminho</classe> \r\n";
            stringXML += "\t\t<left>"+pos.left+"</left> \r\n";
            stringXML += "\t\t<top>"+pos.top+"</top> \r\n";
            stringXML += "\t</info> \r\n"
        }
    }
    stringXML += "</dados>";
    console.log(string);
    //var arquivo = "teste";
    //escreverArquivo();
    //escreverXML();
}

function escreverArquivo() {  
    var fso  = new ActiveXObject("Scripting.FileSystemObject");
    var fh = fso.CreateTextFile("C:/Users/jessica.npfrancisco/Documents/GitHub/projeto_interativo_vi/labirinto/dev/labirinto.txt", true); 
    fh.WriteLine(string);
    fh.Close(); 
}

function escreverXML() {  
    var fso  = new ActiveXObject("Scripting.FileSystemObject");
    var fh = fso.CreateTextFile("C:/Users/jessica.npfrancisco/Documents/GitHub/projeto_interativo_vi/labirinto/dev/labirinto.xml", true); 
    fh.WriteLine(stringXML);
    fh.Close(); 
}