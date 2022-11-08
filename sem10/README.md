### Git, CMake, AVL-деревья

Мы изучим только самые основы работы с Git и CMake.

### Базовый сценарий пользования Git
1. Установим Git по [инструкции](https://git-scm.com/book/ru/v2/%D0%92%D0%B2%D0%B5%D0%B4%D0%B5%D0%BD%D0%B8%D0%B5-%D0%A3%D1%81%D1%82%D0%B0%D0%BD%D0%BE%D0%B2%D0%BA%D0%B0-Git).
2. Создадим аккаунт в [GitLab](https://gitlab.com/).
3. Зайдём в свой профиль, в верхнем верхнем углу найдём меню и перейдём в Projects->View all projects. В правом верхнем углу выберем New project->Create blanc project. Введём название проекта, настройки доступа, оставим галочку напротив создания README.md и нажмем Create project.

Допустим, мы хотим написать задачу о сложении двух чисел, назовём наш репозиторий `sum`.

<p align="center">
  <img src="https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem10/pic2.png" width="500" title="создание пустого репозитория">
</p>

4. Теперь клонируем репозиторий по SSH

<p align="center">
  <img src="https://github.com/konopleva-karina/cpp_seminars_base/blob/main/sem10/clone.png" width="500" title="создание пустого репозитория">
</p>

Нам нужно положить ssh ключ в наш репозиторий. Вначале сгенерируем ED25519 ключ по [гайду](https://docs.gitlab.com/ee/user/ssh.html#generate-an-ssh-key-pair:~:text=id_ecdsa-,Generate%20an%20SSH%20key%20pair,-If%20you%20do) (если его нет) и положим публичный ключ в [Settings->Repository->Deploy keys](https://gitlab.com/konopleva-karina/sum/-/settings/repository#:~:text=active%20Deploy%20Tokens.-,Deploy%20keys,-Expand). По умолчанию все наши ключи лежат в директории `~/.ssh/`.
