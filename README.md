<h1 align="center">Hi 👋, I'm Sergey Makarov</h1>


<p align="left"> <img src="https://komarev.com/ghpvc/?username=sergey030520&label=Profile%20views&color=0e75b6&style=flat" alt="sergey030520" /> </p>

<p align="left"> <a href="https://github.com/ryo-ma/github-profile-trophy"><img src="https://github-profile-trophy.vercel.app/?username=sergey030520" alt="sergey030520" /></a> </p>

- 🔭 I’m currently working on [search_engine](https://github.com/Sergey030520/search_engine)

- 👨‍💻 All of my projects are available at [https://github.com/Sergey030520](https://github.com/Sergey030520)


<h3 align="left">Languages and Tools:</h3>
<p align="left"> 
<a href="https://www.w3schools.com/cpp/" target="_blank" rel="noreferrer"><img src="https://raw.githubusercontent.com/devicons/devicon/master/icons/cplusplus/cplusplus-original.svg" alt="cplusplus" width="40" height="40"/> </a> 
<a href="https://git-scm.com/" target="_blank" rel="noreferrer"> <img src="https://www.vectorlogo.zone/logos/git-scm/git-scm-icon.svg" alt="git" width="40" height="40"/> </a>
<a href="https://cmake.org/" rel="noreferrer"><img src="https://www.vectorlogo.zone/logos/cmake/cmake-icon.svg" alt="Cmake" width="40" height="40"/></a>
</p>

# search_engine

## Оглавление
1. [<p style='font-size: 20px'>Описание</p>](#description_project)
2. [<p style='font-size: 20px'>Инструкция по подключению библиотек</p>](#description_project)
3. [<p style='font-size: 20px'>Сборка проекта и тестирование</p>](#build_and_testing_project)
4. [<p style='font-size: 20px'>Инструкция по сборке проекта</p>](#manual_build_project)
   1. [<p style='font-size: 17px'>Конфигурационный файл поискового движка</p>](#config_file_search_engine)
   2. [<p style='font-size: 17px'>Файл пользовательских запросов</p>](#file_users_requests)
   3. [<p style='font-size: 17px'>Файл ответов на пользовательские запросы</p>](#file_answers_for_requests)
5. [<p style='font-size: 20px'>Пример работы поискового движка</p>](#example_work_search_engine)
## Описание <a name="description_project"></a>

Разработанный поисковой движок представляет из себя консольное приложение
(исполняемый файл, запускаемый на любом сервере или компьютере),
осуществляющий поиск и имеющий возможность настройки через файлы формата
JSON. Применённые в нём решения можно впоследствии встроить в поисковый
движок работающий на веб.

Принципы работы поискового движка следующие:
1. В конфигурационном файле перед запуском приложения задаются названия
   файлов, по которым движок будет осуществлять поиск.
2. Поисковый движок должен самостоятельно обходить все файлы и
   индексировать их так, чтобы потом по любому поисковому запросу находить наиболее
   релевантные документы.
3. Пользователь задаёт запрос через JSON-файл requests.json. Запрос — это
   набор слов, по которым нужно найти документы.
4. Запрос трансформируется в список слов.
5. В индексе ищутся те документы, на которых встречаются все эти слова.
6. Результаты поиска ранжируются, сортируются и отдаются пользователю,
   максимальное количество возможных документов в ответе задаётся в
   конфигурационном файле.
7. В конце программа формирует файл answers.json, в который записывает
   результаты поиска.

## Инструкция по подключению библиотек <a name="manual_connect_library"></a>

В проекте уже сгенированны два файла конфигурации:
1.  [CMakeLists.txt](https://github.com/Sergey030520/search_engine/blob/master/CMakeLists.txt) — основной файл конфигурации и подключает библиотеку для тестированиях программы [googletest]() и библиотеку [nlohmann/json]() для работы с Json файлами;
2.  [CMakeLists.txt](https://github.com/Sergey030520/search_engine/blob/master/src/CMakeLists.txt) — файл конфигурации, который подключает классы программы.

## Сборка проекта и тестирование <a name="build_and_testing_project"></a>
Данный проект был собран и протестирован с помощью таких компиляторов, как [MSVC 2019](https://learn.microsoft.com/en-us/visualstudio/releases/2019/release-notes)
и [GCC](https://gcc.gnu.org/).
Программа разработана на языке C++ 17 стандарта и 
поддерживает следующие операционные системы:
+ Windows 10
+ Windows 11
+ Ubuntu 22.10

## Инструкция по сборке проекта <a name="manual_build_project"></a>

Сборка проекта производится с помощью инструмента [CMake](https://cmake.org/). В терминале компьютера необходимо прописать следующие команды:

```
cmake --build . --config Release --target main
```

### Конфигурационный файл поискового движка <a name="config_file_search_engine"></a>
Пример описания конфигурационного файла [config.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/config.json):
```
{
  "config": {
    "name": "SearchEngine",
    "version": "0.10",
    "max_responses": 5
  },
  "files": [
    "../resorces/file001.txt",
    "../resorces/file002.txt",
    "../resorces/file003.txt",
    "../resorces/file004.txt"
  ]
}
```
Подробнее разберём каждое поле файла [config.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/config.json):
+  config — общая информация, без которой приложение не запускается. Если это поле отсутствует, то при старте программа выбросит исключение и выведет в текстовую консоль ошибку config file is empty. Если отсутствует сам файл config.json, то будет выброшено исключение и выведется ошибка config file is missing.
+  name — поле с названием поискового движка. Оно может быть любым.
+  version — поле с номером версии поискового движка. Поле version должно совпадать с версией самого приложения, иначе будет выдаватся ошибка config.json has incorrect file version. Текущая версия движка 0.10. 
+  max_responses — поле, определяющее один запрос.
+  files содержит пути к файлам, по которым необходимо осуществлять поиск. Внутри списка files лежат пути к файлам. 
+  <путь к файлу>(“../resorces/file001.txt”) — это путь к файлу. Впоследствии по его содержимому будет произведён поиск. Если по этому пути файл не существует, то на экран выводится соответствующая ошибка, но выполнение программы не прекратится. При этом каждый документ содержит не более 1000 слов с максимальной длиной каждого в 100 символов. Слова состоят из строчных латинских букв и разделены одним или несколькими пробелами.

### Файл пользовательских запросов <a name="file_users_requests"></a>
Пример описания файла [requests.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/requests.json):
```
{
  "requests": [
    "milk water",
    "sugar"
  ]
}
```
Разберём каждое поле файла [requests.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/requests.json) подробнее.
+ requests состоит из списка запросов, которые впоследствии будут обработаны поисковым движком. Поле содержит не более 1000 запросов, каждый из которых включает от одного до десяти слов.
+ <содержимое запроса>(“some words”) — поисковый запрос, набор слов, разделённых одним или несколькими пробелами. По ним будет осуществлённ поиск. Все слова состоят из строчных латинских букв.

### Файл ответов на пользовательские запросы <a name="file_answers_for_requests"></a>
Пример описания файла [answers.json](https://github.com/Sergey030520/search_engine/blob/master/file/answers.json):
```
{
  "answers":
      {
        "request000":
        {
          "relevance": 
                [
                  {"docid":2,"rank":1.0}
                ],
          "result":true
        },
        "request001": {
          "relevance": [
            {"docid":1,"rank":1.0}
          ],
          "result":true}
      }
}
```
answers — базовое поле в этом файле, которое содержит ответы на запросы.
+ request001 … 003 — идентификатор запроса, по которому сформирован ответ. Идентификатор запроса формируется автоматически по порядку, в котором находятся запросы в поле requests файла [requests.json](https://github.com/Sergey030520/search_engine/blob/master/file/requests.json). Например:
```
"requests": [
    "some words..", для данной строки id запроса будет равен “request001”
    "some words..", для данной строки id запроса будет равен “request002”
    "some words..", для данной строки id запроса будет равен “request003”
    "some words..", для данной строки id запроса будет равен “request004”
    …
]
```
+   result – результат поиска запроса. Если он принимает значение true, значит по данному запросу найден хотя бы один документ. Если результат имеет значение false, значит ни одного документа не найдено. Тогда других полей в ответе на этот запрос нет.
+ relevance включается в файл answers.json, если на этот запрос удалось найти более одного документа.

## Пример работы поискового движка <a name="example_work_search_engine"></a>
В начале настроим конфигурационный файл, как предстваленно ниже:
```
{
  "config": {
    "name": "SearchEngine",
    "version": "0.10",
    "max_responses": 5
  },
  "files": [
    "C:\\search_engine\\resources\\file001.txt",
    "C:\\search_engine\\resources\\file002.txt",
    "C:\\search_engine\\resources\\file003.txt",
    "C:\\search_engine\\resources\\file004.txt"
  ]
}
```
Затем пропишем пользовательские запросы в файле [requests.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/requests.json):
```
{
  "requests": [
    "milk water",
    "cappuccino salt"
  ]
}
```
И после этого создадим пару текстовых файлов для проверки поискового сервера:
-   [file001.txt](https://github.com/Sergey030520/search_engine/blob/master/resources/file001.txt):
  ```
  milk milk milk milk water water water cappuccino
  ```
  -   [file002.txt](https://github.com/Sergey030520/search_engine/blob/master/resources/file002.txt):
  ```
  americano cappuccino salt milk water
  ```

Для запуска поискового движка необходимо открыть командную строку и перейти в директорию с проектом. 
И затем требуется прописать следующие команды:
+ Для Linux систем:
```
  ./cmake-build-debug/src/search_engine.exe
```
+ Для Windows систем:
```
   .\cmake-build-debug\src\search_engine.exe
```
В рассматриваемом случае программа должна в начале вывести два предупреждения связанные с отсутствием файлов file003.txt и file004.txt и затем произвести поиск заданных пользовательских запросов. Вывод программы представлен на рисунке ниже:

<p>
<img alt="Result of the search engine" src="image/result_program.png"/>
</p>

 Файл [answers.json](https://github.com/Sergey030520/search_engine/blob/master/configuration_files/answers.json) после работы поискового движка:
 ```
 {
  "answers": {
    "request000": {
      "relevance": [
        {
          "docid": 0,
          "rank": 1.0
        },
        {
          "docid": 1,
          "rank": 0.2857142984867096
        }
      ],
      "result": true
    },
    "request001": {
      "relevance": [
        {
          "docid": 1,
          "rank": 1.0
        }
      ],
      "result": true
    }
  }
}
 ```
 
