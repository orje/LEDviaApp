<map version="1.0.1">
<!-- To view this file, download free mind mapping software FreeMind from http://freemind.sourceforge.net -->
<node CREATED="1513188003606" ID="ID_435379548" MODIFIED="1513191847737" TEXT="MoreRunningLED">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Ziel:
    </p>
    <p>
      &#220;ber einen + oder - Button die Anzahl der &quot;rennenden&quot; LED erh&#246;hen und vermindern
    </p>
  </body>
</html></richcontent>
<node CREATED="1513188202084" ID="ID_857246757" MODIFIED="1513188221324" POSITION="right" TEXT="App erg&#xe4;nzen">
<node CREATED="1513188589208" ID="ID_768610870" MODIFIED="1514051496359" TEXT="Buttons">
<icon BUILTIN="button_ok"/>
</node>
<node CREATED="1513190919608" ID="ID_438396013" MODIFIED="1514667990839" TEXT="Variablen">
<icon BUILTIN="button_ok"/>
</node>
</node>
<node CREATED="1513188222950" ID="ID_1963567979" MODIFIED="1514051398127" POSITION="right" TEXT="Model erg&#xe4;nzen">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <ul>
      <li>
        &#160;im Model rechnen

        <ul>
          <li>
            Gruppenanzahl im Model rechnen, da die App nicht wei&#223;, wann Schluss ist, d.h. wieviel LED der Stripe hat.
          </li>
        </ul>
      </li>
    </ul>
    <p>
      
    </p>
  </body>
</html></richcontent>
<node CREATED="1513191125962" ID="ID_317245904" MODIFIED="1514667970994" TEXT="Algorithmus &#xfc;berlegen">
<node CREATED="1514051427742" ID="ID_719678443" MODIFIED="1514667981719" TEXT="Algorithmus im Model integrieren, ohne Kommunikation">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      App liefert + (3P) oder - (4P)
    </p>
    <ul>
      <li>
        variablen erstellt: run_nr, run_nr_index
      </li>
      <li>
        running_fwd, running_bwd, branch bearbeitet
      </li>
    </ul>
  </body>
</html>
</richcontent>
</node>
</node>
</node>
<node CREATED="1514667626890" ID="ID_461477469" MODIFIED="1514667903222" POSITION="left" TEXT="Timing austesten">
<richcontent TYPE="NOTE"><html>
  <head>
    
  </head>
  <body>
    <p>
      Die if-Verschachtelung in der running Funktion scheint das LED timing zu st&#246;ren. Daher ist ein Wert von mindestens 50 ms f&#252;r das COMMUNICATION_TICK, bzw. das Timeout n&#246;tig.
    </p>
  </body>
</html>
</richcontent>
</node>
</node>
</map>
