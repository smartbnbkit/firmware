const char Resource_Index[] PROGMEM = R"RES(<!DOCTYPE html>
<html>
    <head>
        <meta http-equiv="Content-Type" content="text/html; charset=UTF-8">
        <meta name="viewport" content="width=device-width, initial-scale=1.0">
        <title>SmartBnbKit WiFi configuration</title>
        <style type="text/css">
            * {
                box-sizing: border-box;
            }
            body {
                background-color: #f3f3f4;
                font-family: "open sans", "Helvetica Neue", Helvetica, Arial, sans-serif;
                font-size: 13px;
                color: #676a6c;
                overflow-x: hidden;
                height: 100%;
                line-height: 1.42857143;
                margin: 0;
            }
            .middle-box {
                max-width: 400px;
                z-index: 100;
                margin: 0 auto;
                padding-top: 10px;
                width: 300px;
                text-align: center;
            }
            .m-t {
                margin-top: 15px;
            }
            form {
                display: block;
                margin-top: 0em;
            }
            .form-group {
                margin-bottom: 15px;
            }
            .form-control {
                background-color: #FFFFFF;
                background-image: none;
                border: 1px solid #e5e6e7;
                border-radius: 1px;
                color: inherit;
                display: block;
                padding: 6px 12px;
                transition: border-color 0.15s ease-in-out 0s, box-shadow 0.15s ease-in-out 0s;
                width: 100%;
                font-size: 14px;
                line-height: 1.42857143;
                outline: 0;
            }
            .form-control:focus {
              border-color: #02B0D0 !important;
            }
            .btn-primary:hover,
            .btn-primary:focus {
              background-color: #149ab1;
              border-color: #149ab1;
              color: #FFFFFF;
            }
            body.mini-navbar.fixed-sidebar .profile-element, .block {
                display: block !important;
            }
            .m-b {
                margin-bottom: 15px;
            }
            .full-width {
                width: 100% !important;
            }
            .block {
                display: block;
            }
            .btn {
                padding: 6px 12px;
                font-size: 14px;
                font-weight: 400;
                line-height: 1.42857143;
                text-align: center;
                white-space: nowrap;
                vertical-align: middle;
                touch-action: manipulation;
                cursor: pointer;
                background-image: none;
                border: 1px solid transparent;
                border-radius: 3px;
                display: block;
            }
            .btn-primary {
                background-color: #02B0D0;
                border-color: #02B0D0;
                color: #FFFFFF;
            }
            .text-navy {
                color: #02B0D0;
            }
            .ibox-content {
                background-color: #ffffff;
                border-color: #e7eaec;
                border-image: none;
                border-style: solid solid none;
                border-width: 1px 0px;
                margin: 10px 0;
                padding: 5px;
                color: #676a6c;
            }
            .no-margins {
                margin: 0 !important;
            }

            table {
                border-spacing: 0;
                border-collapse: collapse;
                background-color: transparent;
            }

            th, td {
                border-top: 1px solid #e7eaec;
                line-height: 1.42857;
                padding: 8px;
                vertical-align: middle;
            }
            .table>thead:first-child>tr:first-child>td, .table>thead:first-child>tr:first-child>th {
                border-top: 0;
            }
            th {
                text-align: left;
                border-bottom: 1px solid #DDDDDD;
                vertical-align: bottom;
            }
            .loader {
                -webkit-animation: spin 1s linear infinite;
                -moz-animation: spin 1s linear infinite;
                animation: spin 1s linear infinite;
            }
            @-moz-keyframes spin { 100% { -moz-transform: rotate(360deg); } }
            @-webkit-keyframes spin { 100% { -webkit-transform: rotate(360deg); } }
            @keyframes spin { 100% { -webkit-transform: rotate(360deg); transform: rotate(360deg); } }
        </style>
        <script type="text/javascript">
            function post(url, data, callback) {
                var http = new XMLHttpRequest();
                http.onreadystatechange = function() {
                    if (this.readyState == 4 && callback)
                        callback(this.responseText);
                };
                http.open('POST', url, true);
                http.timeout = 60000;
                http.send(data);
            }
            function save() {
                var ssid = document.getElementById('ssid').value;
                var pass = document.getElementById('password').value;
                var api_login = document.getElementById('api_login').value;
                var api_pass = document.getElementById('api_pass').value;
                
                post('/save', 'ssid=' + encodeURIComponent(ssid) +
                              '&password=' + encodeURIComponent(pass) +
                              '&api_login=' + encodeURIComponent(api_login) +
                              '&api_pass=' + encodeURIComponent(api_pass), function(resp) {
                    alert('Saved ' + resp); // Todo: make this pretty
                    window.close();
                });
            }
            
            post('/scan', '', function (data) {
                var html = '';
                var results = JSON.parse(data);
                if (!data || !results) {
                    html = '<tr><td colspan="2" valign="middle" align="center">No networks found. Refresh to scan again.</td></tr>';
                } else {
                    for (var i in results) {
                        var lock = !results[i].open? '<div style="position: absolute; left: 3px;"><svg width="14" height="14" viewBox="0 0 1792 1792" xmlns="http://www.w3.org/2000/svg"><path d="M640 768h512v-192q0-106-75-181t-181-75-181 75-75 181v192zm832 96v576q0 40-28 68t-68 28h-960q-40 0-68-28t-28-68v-576q0-40 28-68t68-28h32v-192q0-184 132-316t316-132 316 132 132 316v192h32q40 0 68 28t28 68z" fill="#000"/></svg></div>' : '';
                        
                        html += '<tr onclick="document.getElementById(\'ssid\').value = this.getElementsByTagName(\'td\')[0].getElementsByTagName(\'span\')[0].innerHTML" style="cursor: pointer;"> \
                                    <td style="position: relative">' + lock + '<span>' + results[i].ssid + '</span></td> \
                                    <td class="text-navy"><svg width="14" height="14" viewBox="0 0 1792 1792" xmlns="http://www.w3.org/2000/svg"><path d="M896 1523q-20 0-93-73.5t-73-93.5q0-32 62.5-54t103.5-22 103.5 22 62.5 54q0 20-73 93.5t-93 73.5zm270-271q-2 0-40-25t-101.5-50-128.5-25-128.5 25-101 50-40.5 25q-18 0-93.5-75t-75.5-93q0-13 10-23 78-77 196-121t233-44 233 44 196 121q10 10 10 23 0 18-75.5 93t-93.5 75zm273-272q-11 0-23-8-136-105-252-154.5t-268-49.5q-85 0-170.5 22t-149 53-113.5 62-79 53-31 22q-17 0-92-75t-75-93q0-12 10-22 132-132 320-205t380-73 380 73 320 205q10 10 10 22 0 18-75 93t-92 75zm271-271q-11 0-22-9-179-157-371.5-236.5t-420.5-79.5-420.5 79.5-371.5 236.5q-11 9-22 9-17 0-92.5-75t-75.5-93q0-13 10-23 187-186 445-288t527-102 527 102 445 288q10 10 10 23 0 18-75.5 93t-92.5 75z" fill="#02B0D0" /></svg> ' + results[i].strength +'%</td> \
                                </tr>';
                    }
                }
                document.getElementById('scan_results').innerHTML = html;
            });
        </script>
    </head>
    <body>
        <div class="middle-box">
            <div>
                <div class="logo"><svg xmlns="http://www.w3.org/2000/svg" width="300" height="180" style="padding: 15px;" viewBox="0 0 331 198" shape-rendering="geometricPrecision" text-rendering="geometricPrecision" image-rendering="optimizeQuality" fill-rule="evenodd" clip-rule="evenodd"><defs><style>.fil0 {fill:#02B0D0} .fil2 {fill:#221F1F} .fil1 {fill:#F05B89} .fil3 {fill:white} </style></defs><g id="Layer_x0020_1"><g id="_269665943488"><path class="fil0" d="M15 170c-4 0-5 2-5 4 0 6 17 3 17 15 0 6-4 9-12 9-6 0-10-3-12-6v-1c0-1 1-2 2-2s2 0 2 1c2 2 5 3 8 3 4 0 6-1 6-4 0-7-17-4-17-15 0-5 3-9 11-9 5 0 9 2 10 5 1 0 1 1 1 1 0 2-1 3-3 3 0 0-1-1-2-1-1-2-3-3-6-3zm32 21l-7-13v17c0 2-1 3-3 3-1 0-3-1-3-3v-27c0-1 2-2 3-2s2 0 2 1l10 18 10-18c1-1 2-1 3-1s2 1 2 2v27c0 2-1 3-2 3-2 0-3-1-3-3v-17l-7 13c-1 1-2 1-3 1s-1 0-2-1zm33-2l-3 7c-1 1-2 2-3 2s-2-1-2-3v-1l11-27s1-1 2-1c2 0 2 1 3 1l11 27v1c0 2-1 3-3 3-1 0-2-1-2-2l-3-7H80zm5-15l-4 10h8l-4-10zm26 11v10c0 2-1 3-2 3-2 0-3-1-3-3v-26c0-2 1-3 3-3h9c6 0 10 4 10 10 0 4-3 8-8 9l7 8c1 1 1 2 1 2 0 2-1 3-3 3-1 0-1-1-2-1l-8-12h-4zm0-14v10h7c3 0 4-3 4-5 0-3-1-5-4-5h-7zm37 0v24c0 2-1 3-2 3-2 0-3-1-3-3v-24h-7c-2 0-3-1-3-3 0-1 1-2 3-2h20c1 0 2 1 2 2 0 2-1 3-2 3h-8z"/><path class="fil1" d="M168 197c-2 0-3-1-3-2v-26c0-2 1-3 3-3h8c7 0 10 4 10 8 0 3-2 6-4 6 4 2 5 4 5 8 0 6-3 9-10 9h-9zm2-18h6c3 0 4-2 4-4 0-3-1-4-4-4h-6v8zm0 14h7c3 0 5-2 5-5s-2-5-5-5h-7v10zm49-25v27c0 2-1 3-2 3s-2-1-3-1l-14-20v18c0 2-1 3-2 3-2 0-3-1-3-3v-27c0-1 1-2 3-2 1 0 1 0 2 1l14 20v-19c0-1 1-2 3-2 1 0 2 1 2 2zm12 29c-1 0-3-1-3-2v-26c0-2 2-3 3-3h9c7 0 9 4 9 8 0 3-1 6-3 6 3 2 5 4 5 8 0 6-4 9-11 9h-9zm3-18h6c3 0 4-2 4-4 0-3-1-4-4-4h-6v8zm0 14h6c4 0 5-2 5-5s-1-5-5-5h-6v10z"/><path class="fil0" d="M264 179l11-13h2c2 0 3 1 3 2s0 1-1 2l-8 10 10 14v1c0 2-1 3-2 3s-2-1-2-1l-10-14-3 3v9c0 2-1 3-3 3-1 0-2-1-2-3v-27c0-1 1-2 2-2 2 0 3 1 3 2v11zm30 16c0 2-2 3-3 3s-3-1-3-3v-27c0-1 2-2 3-2s3 1 3 2v27zm22-24v24c0 2-2 3-3 3-2 0-3-1-3-3v-24h-7c-1 0-2-1-2-3 0-1 1-2 2-2h20c1 0 2 1 2 2 0 2-1 3-2 3h-7zM250 140H81c-16 0-29-13-29-29V29C52 13 65 0 81 0h169c16 0 29 13 29 29v82c0 16-13 29-29 29z"/><path class="fil2" d="M147 70c0-17-14-31-32-31-17 0-31 14-31 31s14 31 31 31c18 0 32-14 32-31z"/><path class="fil3" d="M115 26c-24 0-44 20-44 44 0 25 20 45 44 45 25 0 45-20 45-45 0-24-20-44-45-44zM84 70c0-17 14-31 31-31 18 0 32 14 32 31s-14 31-32 31c-17 0-31-14-31-31z"/><path class="fil2" d="M216 39c-18 0-32 14-32 31s14 31 32 31c17 0 31-14 31-31s-14-31-31-31z"/><path class="fil3" d="M216 26c-25 0-45 20-45 44 0 25 20 45 45 45 24 0 44-20 44-45 0-24-20-44-44-44zm0 76c-18 0-32-15-32-32s14-31 32-31c17 0 31 14 31 31s-14 32-31 32z"/><circle class="fil1" cx="20" cy="119" r="20"/><circle class="fil1" cx="20" cy="61" r="14"/><circle class="fil1" cx="20" cy="11" r="11"/><circle class="fil1" cx="311" cy="20" r="20"/><circle class="fil1" cx="311" cy="78" r="14"/><circle class="fil1" cx="311" cy="127" r="11"/></g></g></svg></div>
                <p style="margin-top: -5px;">WiFi configuration</p>
                
                <div class="ibox-content">
                    <table class="table table-hover no-margins full-width">
                        <thead>
                        <tr>
                            <th>SSID</th>
                            <th>Signal strength</th>
                        </tr>
                        </thead>
                        <tbody id="scan_results">
                            <tr><td colspan="2" valign="middle" align="center">
                                <svg class="loader" width="32" height="32" viewBox="0 0 100 100" xmlns="http://www.w3.org/2000/svg" preserveAspectRatio="xMidYMid"><path d="M10,50c0,0,0,0.5,0.1,1.4c0,0.5,0.1,1,0.2,1.7c0,0.3,0.1,0.7,0.1,1.1c0.1,0.4,0.1,0.8,0.2,1.2c0.2,0.8,0.3,1.8,0.5,2.8 c0.3,1,0.6,2.1,0.9,3.2c0.3,1.1,0.9,2.3,1.4,3.5c0.5,1.2,1.2,2.4,1.8,3.7c0.3,0.6,0.8,1.2,1.2,1.9c0.4,0.6,0.8,1.3,1.3,1.9 c1,1.2,1.9,2.6,3.1,3.7c2.2,2.5,5,4.7,7.9,6.7c3,2,6.5,3.4,10.1,4.6c3.6,1.1,7.5,1.5,11.2,1.6c4-0.1,7.7-0.6,11.3-1.6 c3.6-1.2,7-2.6,10-4.6c3-2,5.8-4.2,7.9-6.7c1.2-1.2,2.1-2.5,3.1-3.7c0.5-0.6,0.9-1.3,1.3-1.9c0.4-0.6,0.8-1.3,1.2-1.9 c0.6-1.3,1.3-2.5,1.8-3.7c0.5-1.2,1-2.4,1.4-3.5c0.3-1.1,0.6-2.2,0.9-3.2c0.2-1,0.4-1.9,0.5-2.8c0.1-0.4,0.1-0.8,0.2-1.2 c0-0.4,0.1-0.7,0.1-1.1c0.1-0.7,0.1-1.2,0.2-1.7C90,50.5,90,50,90,50s0,0.5,0,1.4c0,0.5,0,1,0,1.7c0,0.3,0,0.7,0,1.1 c0,0.4-0.1,0.8-0.1,1.2c-0.1,0.9-0.2,1.8-0.4,2.8c-0.2,1-0.5,2.1-0.7,3.3c-0.3,1.2-0.8,2.4-1.2,3.7c-0.2,0.7-0.5,1.3-0.8,1.9 c-0.3,0.7-0.6,1.3-0.9,2c-0.3,0.7-0.7,1.3-1.1,2c-0.4,0.7-0.7,1.4-1.2,2c-1,1.3-1.9,2.7-3.1,4c-2.2,2.7-5,5-8.1,7.1 c-0.8,0.5-1.6,1-2.4,1.5c-0.8,0.5-1.7,0.9-2.6,1.3L66,87.7l-1.4,0.5c-0.9,0.3-1.8,0.7-2.8,1c-3.8,1.1-7.9,1.7-11.8,1.8L47,90.8 c-1,0-2-0.2-3-0.3l-1.5-0.2l-0.7-0.1L41.1,90c-1-0.3-1.9-0.5-2.9-0.7c-0.9-0.3-1.9-0.7-2.8-1L34,87.7l-1.3-0.6 c-0.9-0.4-1.8-0.8-2.6-1.3c-0.8-0.5-1.6-1-2.4-1.5c-3.1-2.1-5.9-4.5-8.1-7.1c-1.2-1.2-2.1-2.7-3.1-4c-0.5-0.6-0.8-1.4-1.2-2 c-0.4-0.7-0.8-1.3-1.1-2c-0.3-0.7-0.6-1.3-0.9-2c-0.3-0.7-0.6-1.3-0.8-1.9c-0.4-1.3-0.9-2.5-1.2-3.7c-0.3-1.2-0.5-2.3-0.7-3.3 c-0.2-1-0.3-2-0.4-2.8c-0.1-0.4-0.1-0.8-0.1-1.2c0-0.4,0-0.7,0-1.1c0-0.7,0-1.2,0-1.7C10,50.5,10,50,10,50z" fill="#02B0D0"></svg>
                            </td></tr>
                        </tbody>
                    </table>
                </div>

                <h3>Please enter your WiFi credentials</h3>
                <form class="m-t" method="post">
                    <div class="form-group"><input type="text" class="form-control" placeholder="SSID" required name="ssid" id="ssid" value="%ssid%"></div>
                    <div class="form-group"><input type="password" class="form-control" placeholder="Password" id="password" value="%pass%"> </div>
                    <h3>Your API credentials:</h3>
                    <div class="form-group"><input type="text" class="form-control" placeholder="API username" required id="api_login" value="%api_login%"></div>
                    <div class="form-group"><input type="password" class="form-control" placeholder="API password" required id="api_pass" value="%api_pass%"> </div>
                    <button onclick="save()" class="btn btn-primary block full-width m-b">Save and reboot</button>
                </form>
                <p class="m-t"> <small>Toptal © 2016</small> </p>
            </div>
        </div>
    </body>
</html>)RES";
