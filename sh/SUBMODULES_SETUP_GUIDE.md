# 🔧 Guia de Organização de Submódulos - 42

Sistema completo para organizar repositório 42 com estrutura de submódulos do GitHub.

## 📊 Status Atual

### ✅ Já Submódulos
- `piscine/`: c00-c13, shell00-01, bsq (18 submódulos)
- `42_common_core/`: libft, get_next_line, ft_printf (3 submódulos)

### 🔄 Precisa Converter (têm .git)
- **rank02**: pipex, push_swap, so_long
- **rank03**: minishell, philosophers
- **rank04**: cub3d, miniRT, netpractice
- **rank05**: cpp_modules, inception, webserv
- **rank06**: ft_transcendence
- **extras**: ft_irc, libasm, malloc

**Total**: 15 projetos

### 🆕 Precisa Criar Estrutura
- **42_specializations**: 32 projetos vazios em 6 categorias
  - ai (5 projetos)
  - cybersecurity (5 projetos)
  - devops (5 projetos)
  - graphics (4 projetos)
  - networking (8 projetos)
  - systems (8 projetos)

---

## 🚀 Scripts Disponíveis

### 1️⃣ `auto_convert_submodules.sh` ⭐ RECOMENDADO
**Uso**: Conversão automática completa de projetos existentes

```bash
./auto_convert_submodules.sh
```

**O que faz:**
- ✅ Cria repos no GitHub para cada projeto
- ✅ Push automático do código
- ✅ Remove pastas locais
- ✅ Adiciona como submódulos
- ✅ Commit final

**Requer**: GitHub CLI (`gh`) instalado e autenticado

---

### 2️⃣ `init_specializations.sh`
**Uso**: Cria estrutura inicial para projetos vazios

```bash
./init_specializations.sh
```

**O que faz:**
- 📁 Cria estrutura: src/, include/, tests/, docs/
- 📝 README customizado por categoria
- ⚙️ Makefile funcional
- 🔧 .gitignore configurado
- 🚀 GitHub Actions CI
- 📦 Git init + commit inicial

---

### 3️⃣ `auto_push_specializations.sh`
**Uso**: Push e conversão de specializations

```bash
./auto_push_specializations.sh
```

**O que faz:**
- ✅ Cria repos no GitHub (padrão: `42-categoria-projeto`)
- ✅ Push de estruturas criadas
- ✅ Conversão para submódulos

**Requer**: Rodar `init_specializations.sh` antes

---

### 4️⃣ `setup_submodules.sh`
**Uso**: Menu interativo (modo manual)

```bash
./setup_submodules.sh
```

**Opções:**
1. Converter projetos existentes (manual)
2. Criar estruturas specializations (manual)
3. Ambos
4. Gerar script de automação

---

## 📋 Fluxo Recomendado

### ✨ Modo Automático Completo

```bash
# 1. Instalar GitHub CLI (se necessário)
# Ubuntu/Debian:
sudo apt install gh
# macOS:
brew install gh

# 2. Autenticar
gh auth login

# 3. Converter projetos existentes
./auto_convert_submodules.sh

# 4. Criar estruturas de specializations
./init_specializations.sh

# 5. Push specializations
./auto_push_specializations.sh

# 6. Push final do repositório principal
git push origin main

# 7. Atualizar submódulos
git submodule update --init --recursive
```

**Tempo estimado**: 10-15 minutos

---

### 🛠️ Modo Manual (Passo a Passo)

#### Parte 1: Converter Projetos Existentes

Para cada projeto em rank02-06 e extras:

```bash
cd 42_common_core/rank02/pipex  # exemplo

# Criar repo no GitHub
gh repo create Milsonyujiaoki/pipex --public

# Push
git remote set-url origin git@github.com:Milsonyujiaoki/pipex.git
git push -u origin main

# Voltar para raiz
cd /home/dev-yuji/projetos/42

# Remover e adicionar como submódulo
git rm -r --cached 42_common_core/rank02/pipex
rm -rf 42_common_core/rank02/pipex
git submodule add git@github.com:Milsonyujiaoki/pipex.git 42_common_core/rank02/pipex
git commit -m "feat: add pipex as submodule"
```

Repetir para todos os 15 projetos.

#### Parte 2: Specializations

```bash
# Criar estrutura
./init_specializations.sh

# Para cada projeto, criar repo e push
cd 42_specializations/ai/neural_network  # exemplo

gh repo create Milsonyujiaoki/42-ai-neural_network --public
git remote add origin git@github.com:Milsonyujiaoki/42-ai-neural_network.git
git push -u origin main

# Adicionar como submódulo
cd /home/dev-yuji/projetos/42
git rm -r --cached 42_specializations/ai/neural_network
rm -rf 42_specializations/ai/neural_network
git submodule add git@github.com:Milsonyujiaoki/42-ai-neural_network.git 42_specializations/ai/neural_network
git commit -m "feat: add ai/neural_network as submodule"
```

---

## 🔍 Verificação

```bash
# Listar todos submódulos
git submodule status

# Verificar .gitmodules
cat .gitmodules

# Contar submódulos
git submodule status | wc -l

# Atualizar todos
git submodule update --init --recursive

# Clonar repo com submódulos
git clone --recurse-submodules git@github.com:Milsonyujiaoki/42.git
```

---

## 📂 Estrutura Final Esperada

```
42/
├── .gitmodules                    # 66 submódulos total
├── piscine/
│   ├── c00/                      # submódulo
│   ├── c01-c13/                  # submódulos
│   ├── shell00-01/               # submódulos
│   └── bsq/                      # submódulo
├── 42_common_core/
│   ├── libft/                    # submódulo
│   ├── get_next_line/            # submódulo
│   ├── ft_printf/                # submódulo
│   ├── rank02/
│   │   ├── pipex/                # submódulo
│   │   ├── push_swap/            # submódulo
│   │   └── so_long/              # submódulo
│   ├── rank03/
│   │   ├── minishell/            # submódulo
│   │   └── philosophers/         # submódulo
│   ├── rank04/
│   │   ├── cub3d/                # submódulo
│   │   ├── miniRT/               # submódulo
│   │   └── netpractice/          # submódulo
│   ├── rank05/
│   │   ├── cpp_modules/          # submódulo
│   │   ├── inception/            # submódulo
│   │   └── webserv/              # submódulo
│   └── rank06/
│       └── ft_transcendence/     # submódulo
├── 42_specializations/
│   ├── ai/                       # 5 submódulos
│   ├── cybersecurity/            # 5 submódulos
│   ├── devops/                   # 5 submódulos
│   ├── graphics/                 # 4 submódulos
│   ├── networking/               # 8 submódulos
│   └── systems/                  # 8 submódulos
└── extras/
    ├── ft_irc/                   # submódulo
    ├── libasm/                   # submódulo
    └── malloc/                   # submódulo
```

**Total**: 66 submódulos

---

## 🐛 Troubleshooting

### Erro: "already exists in the index"
```bash
git rm -r --cached <pasta>
git submodule add <url> <pasta>
```

### URL incompleta em .gitmodules
```bash
# Editar manualmente
nano .gitmodules

# Ou atualizar via git
git config -f .gitmodules submodule.<path>.url git@github.com:user/repo.git
```

### Submódulo não inicializa
```bash
git submodule deinit -f <pasta>
git submodule update --init <pasta>
```

### Limpar cache de submódulos
```bash
rm -rf .git/modules/<path>
git rm -r --cached <pasta>
```

---

## 📚 Recursos

- [Git Submodules Documentation](https://git-scm.com/book/en/v2/Git-Tools-Submodules)
- [GitHub CLI](https://cli.github.com/)
- [42 Intra](https://intra.42.fr/)

---

## ✅ Checklist Final

- [ ] GitHub CLI instalado e autenticado
- [ ] Scripts com permissão de execução
- [ ] Backup do repositório atual
- [ ] Executar `auto_convert_submodules.sh`
- [ ] Executar `init_specializations.sh`
- [ ] Executar `auto_push_specializations.sh`
- [ ] Verificar `.gitmodules`
- [ ] Push do repositório principal
- [ ] Testar clone recursivo
- [ ] Atualizar README principal

---

**Autor**: [@Milsonyujiaoki](https://github.com/Milsonyujiaoki)  
**Data**: 2026-05-21
